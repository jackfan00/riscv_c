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
REG8 ext_cmd_rwbyte;
BIT ext_rsp_valid;
BIT ext_rsp_ready;
REG32 ext_rsp_rdata;
BIT ext_rsp_read;
BIT ext_rsp_rden;
REG8 ext_rsp_regidx;
REG8 ext_cmd_regidx;
BIT ext_cmd_rden;

#endif //EXT_WRITE_CODERAM_H