#ifndef DTCMMERGE_H
#define DTCMMERGE_H
#include "reg.h"
void dtcmmerge();
void dtcmmerge_clked();


REG8 dtcmmergeFIFO_widx_clked;
REG8 dtcmmergeFIFO_ridx_clked;
REG8 dtcmmergeFIFO_clked;//[DTCMMERGEFIFODEPTH];
BIT dtcmmerge_extpri_clked;

BIT dtcmmerge_o_cmd_valid;
BIT dtcmmerge_o_cmd_ready;
BIT dtcmmerge_o_cmd_read;
REG32 dtcmmerge_o_cmd_adr;
REG32 dtcmmerge_o_cmd_data;
REG8 dtcmmerge_o_cmd_rwbyte;
BIT dtcmmerge_o_rsp_valid;
BIT dtcmmerge_o_rsp_ready;
BIT dtcmmerge_o_rsp_read;
REG32 dtcmmerge_o_rsp_rdata;
REG8 dtcmmergeFIFO_widx;
REG8 dtcmmergeFIFO_ridx;
REG8 dtcmmergeFIFO;
BIT dtcmmergeFIFO_wen;
BIT dtcmmergeFIFO_ren;
REG8 dtcmmergeFIFO_wid;
REG8 dtcmmergeFIFO_rid;
BIT dtcmmergeFIFOfull;
BIT dtcmmergeFIFOempty;
BIT ifupri;
BIT dtcmmerge_extpri;

BIT ext2dtcm_cmd_valid;
BIT ext2dtcm_cmd_ready;
BIT ext2dtcm_cmd_read;
REG32 ext2dtcm_cmd_adr;
REG32 ext2dtcm_cmd_data;
REG8 ext2dtcm_cmd_rwbyte;
BIT ext2dtcm_rsp_valid;
BIT ext2dtcm_rsp_ready;
BIT ext2dtcm_rsp_read;
REG32 ext2dtcm_rsp_rdata;

#endif //DTCMMERGE_H