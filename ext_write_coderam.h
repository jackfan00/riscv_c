#ifndef EXT_WRITE_CODERAM_H
#define EXT_WRITE_CODERAM_H
#include "reg.h"
void ext_write_coderam();
void ext_write_coderam_clked();

//input
BIT ext_cmd_ready;
BIT randomcycle_clked;
BIT downloadper_clked;
REG32 codeindex_clked;
REG32 download_codesize;

//output
BIT downloadstart;
BIT downloadcomplete;
BIT ext_cmd_valid;
BIT ext_cmd_read;
REG32 ext_cmd_addr;
REG32 ext_cmd_wdata;

#endif //EXT_WRITE_CODERAM_H