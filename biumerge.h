#ifndef BIUMERGE_H
#define BIUMERGE_H
#include "reg.h"
void biumerge();
void biumerge_clked();


REG8 biumergeFIFO_widx_clked;
REG8 biumergeFIFO_ridx_clked;
REG8 biumergeFIFO_clked[BIUMERGEFIFODEPTH];
BIT biumerge_ifupri_clked;

BIT biumerge_o_cmd_valid;
BIT biumerge_o_cmd_ready;
BIT biumerge_o_cmd_read;
REG32 biumerge_o_cmd_adr;
REG32 biumerge_o_cmd_data;
REG8 biumerge_o_cmd_rwbyte;
BIT biumerge_o_rsp_valid;
BIT biumerge_o_rsp_ready;
BIT biumerge_o_rsp_read;
REG32 biumerge_o_rsp_rdata;
REG8 biumergeFIFO_widx;
REG8 biumergeFIFO_ridx;
REG8 biumergeFIFO;
BIT biumergeFIFO_wen;
BIT biumergeFIFO_ren;
REG8 biumergeFIFO_wid;
REG8 biumergeFIFO_rid;
BIT biumergeFIFOfull;
BIT biumergeFIFOempty;
BIT biumerge_ifupri;

#endif //BIUMERGE_H