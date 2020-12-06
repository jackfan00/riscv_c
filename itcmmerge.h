#ifndef ITCMMERGE_H
#define ITCMMERGE_H
#include "reg.h"


REG8 itcmmergeFIFO_widx_clked;
REG8 itcmmergeFIFO_ridx_clked;
REG8 itcmmergeFIFO_clked[ITCMMERGEFIFODEPTH];
BIT itcmmerge_ifupri_clked;
BIT itcmmerge_extpri_clked;

BIT itcmmerge_o_cmd_valid;
BIT itcmmerge_o_cmd_ready;
BIT itcmmerge_o_cmd_read;
REG32 itcmmerge_o_cmd_adr;
REG32 itcmmerge_o_cmd_data;
REG8 itcmmerge_o_cmd_rwbyte;
BIT itcmmerge_o_rsp_valid;
BIT itcmmerge_o_rsp_ready;
REG32 itcmmerge_o_rsp_rdata;
REG8 itcmmergeFIFO_widx;
REG8 itcmmergeFIFO_ridx;
REG8 itcmmergeFIFO;
BIT itcmmergeFIFO_wen;
BIT itcmmergeFIFO_ren;
REG8 itcmmergeFIFO_wid;
REG8 itcmmergeFIFO_rid;
BIT itcmmergeFIFOfull;
BIT itcmmergeFIFOempty;
BIT itcmmerge_ifupri;
BIT itcmmerge_extpri;

BIT ext2itcm_cmd_valid;
BIT ext2itcm_cmd_ready;
BIT ext2itcm_cmd_read;
REG32 ext2itcm_cmd_adr;
REG32 ext2itcm_cmd_data;
REG8 ext2itcm_cmd_rwbyte;
BIT ext2itcm_rsp_valid;
BIT ext2itcm_rsp_ready;
REG32 ext2itcm_rsp_rdata;

#endif //ITCMMERGE_H