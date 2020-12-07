#ifndef CLINT_H
#define CLINT_H
#include "reg.h"

#define CLINT_MSIP      0x02000000
#define CLINT_MTIMECMP  0x02004000
#define CLINT_MTIMECMPH 0x02004004
#define CLINT_MTIME     0x0200BFF8
#define CLINT_MTIMEH    0x0200BFFC

//input
BIT clint_msip_clked;
BIT clint_mtip_clked;
REG32 clint_mtimecmp_clked;
REG32 clint_mtimecmph_clked;
REG32 clint_mtime_clked;
REG32 clint_mtimeh_clked;
BIT clint_read_clked;
REG32 clint_regradr_clked;

//output
BIT clint_msip;
BIT clint_mtip;
REG32 clint_mtimecmp;
REG32 clint_mtimecmph;
REG32 clint_mtime;
REG32 clint_mtimeh;
BIT clint_regcs;
BIT clint_regw;
REG32 clint_regwdata;
REG32 clint_regwadr;
REG32 clint_regradr;
BIT clint_cmd_valid;
BIT clint_cmd_ready;
BIT clint_cmd_read;
REG32 clint_cmd_adr;
REG32 clint_cmd_data;
BIT clint_rsp_valid;
BIT clint_rsp_ready;
REG32 clint_rsp_rdata;
BIT clint_read;

#endif //CLINT_H