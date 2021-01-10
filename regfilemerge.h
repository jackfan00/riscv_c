#ifndef REGFILEMERGE_H
#define REGFILEMERGE_H
void regfilemerge();
void regfilemerge_clked();

#include "reg.h"


REG8 regfilemergeFIFO_widx_clked;
REG8 regfilemergeFIFO_ridx_clked;
REG8 regfilemergeFIFO_clked;//[ITCMMERGEFIFODEPTH];
BIT divpri_clked;
BIT mulpri_clked;
BIT s2pri_clked;

BIT regfilemerge_o_cmd_valid;
BIT regfilemerge_o_cmd_ready;
BIT regfilemerge_o_cmd_read;
REG32 regfilemerge_o_cmd_adr;
REG32 regfilemerge_o_cmd_data;
REG8 regfilemerge_o_cmd_rwbyte;
BIT regfilemerge_o_rsp_valid;
BIT regfilemerge_o_rsp_ready;
BIT regfilemerge_o_rsp_read;
REG32 regfilemerge_o_rsp_rdata;
REG8 regfilemergeFIFO_widx;
REG8 regfilemergeFIFO_ridx;
REG8 regfilemergeFIFO;
BIT regfilemergeFIFO_wen;
BIT regfilemergeFIFO_ren;
REG8 regfilemergeFIFO_wid;
REG8 regfilemergeFIFO_rid;
BIT regfilemergeFIFOfull;
BIT regfilemergeFIFOempty;
BIT divpri;
BIT mulpri;
BIT s2pri;
BIT regfile_wrdiv;
BIT regfile_wrload;

#endif //REGFILEMERGE_H