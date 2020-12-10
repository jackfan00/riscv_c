#ifndef LSUBUSSPLIT_H
#define LSUBUSSPLIT_H
void lsubussplit();
void lsubussplit_clked();

#include "reg.h"


//last target dont need to compare targetbase
REG8 lsusplit_TARGETBASE[LSUSPLITTARGETNUM];  //MSB

BIT lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM];
BIT lsusplit_o_bus_cmd_ready[LSUSPLITTARGETNUM];
BIT lsusplit_o_bus_cmd_read[LSUSPLITTARGETNUM];
REG8 lsusplit_o_bus_cmd_rwbyte[LSUSPLITTARGETNUM];
REG32 lsusplit_o_bus_cmd_adr[LSUSPLITTARGETNUM];
REG32 lsusplit_o_bus_cmd_data[LSUSPLITTARGETNUM];
BIT lsusplit_o_bus_rsp_valid[LSUSPLITTARGETNUM];
BIT lsusplit_o_bus_rsp_ready[LSUSPLITTARGETNUM];
BIT lsusplit_o_bus_rsp_read[LSUSPLITTARGETNUM];
REG32 lsusplit_o_bus_rsp_rdata[LSUSPLITTARGETNUM];
REG8 lsutransacFIFO_clked[LSUSPLIFIFODEPTH];
REG8 lsuregfileidxFIFO_clked[LSUSPLIFIFODEPTH];
BIT lsuregfilerdenFIFO_clked[LSUSPLIFIFODEPTH];
REG8 lsutransacFIFO_widx_clked;
REG8 lsutransacFIFO_ridx_clked;

BIT lsusplit_i_bus_cmd_valid;
BIT lsusplit_i_bus_cmd_ready;
BIT lsusplit_i_bus_cmd_read;
REG8 lsusplit_i_bus_cmd_rwbyte;
REG32 lsusplit_i_bus_cmd_adr;
REG32 lsusplit_i_bus_cmd_data;
BIT lsusplit_i_bus_rsp_valid;
BIT lsusplit_i_bus_rsp_ready;
BIT lsusplit_i_bus_rsp_read;
REG32 lsusplit_i_bus_rsp_rdata;
REG8 lsusplit_i_bus_rsp_regidx;
BIT lsusplit_i_bus_rsp_rden;
REG8 lsutransacFIFO;
REG8 lsuregfileidxFIFO;
BIT lsuregfilerdenFIFO;
REG8 lsutransacFIFO_wid;
REG8 lsutransacFIFO_rid;
BIT lsutransacFIFO_wen;
REG8 lsutransacFIFO_widx;
BIT lsutransacFIFO_ren;
REG8 lsutransacFIFO_ridx;
BIT lsutransacFIFOempty;
BIT lsutransacFIFOfull;
BIT real_lsusplit_i_bus_cmd_valid;
REG8 nxtwrapped_lsutransacFIFO_widx;
BIT lsu2biu_cmd_valid;
BIT lsu2biu_cmd_ready;
BIT lsu2biu_cmd_read;
REG32 lsu2biu_cmd_adr;
REG32 lsu2biu_cmd_data;
REG8 lsu2biu_cmd_rwbyte;
BIT lsu2biu_rsp_valid;
BIT lsu2biu_rsp_ready;
BIT lsu2biu_rsp_read;
REG32 lsu2biu_rsp_rdata;

BIT lsu2dtcm_cmd_valid;
BIT lsu2dtcm_cmd_ready;
BIT lsu2dtcm_cmd_read;
REG32 lsu2dtcm_cmd_adr;
REG32 lsu2dtcm_cmd_data;
REG8 lsu2dtcm_cmd_rwbyte;
BIT lsu2dtcm_rsp_valid;
BIT lsu2dtcm_rsp_ready;
BIT lsu2dtcm_rsp_read;
REG32 lsu2dtcm_rsp_rdata;

BIT lsu2itcm_cmd_valid;
BIT lsu2itcm_cmd_ready;
BIT lsu2itcm_cmd_read;
REG32 lsu2itcm_cmd_adr;
REG32 lsu2itcm_cmd_data;
REG8 lsu2itcm_cmd_rwbyte;
BIT lsu2itcm_rsp_valid;
BIT lsu2itcm_rsp_ready;
BIT lsu2itcm_rsp_read;
REG32 lsu2itcm_rsp_rdata;

#endif //LSUBUSSPLIT_H