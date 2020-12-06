#ifndef IFUBUSSPLIT_H
#define IFUBUSSPLIT_H
#include "reg.h"


//last target dont need to compare targetbase
REG8 ifusplit_TARGETBASE[IFUSPLITTARGETNUM];  //MSB

BIT ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM];
BIT ifusplit_o_bus_cmd_ready[IFUSPLITTARGETNUM];
BIT ifusplit_o_bus_cmd_read[IFUSPLITTARGETNUM];
REG32 ifusplit_o_bus_cmd_adr[IFUSPLITTARGETNUM];
REG32 ifusplit_o_bus_cmd_data[IFUSPLITTARGETNUM];
REG8 ifusplit_o_bus_cmd_rwbyte[IFUSPLITTARGETNUM];
BIT ifusplit_o_bus_rsp_valid[IFUSPLITTARGETNUM];
BIT ifusplit_o_bus_rsp_ready[IFUSPLITTARGETNUM];
REG32 ifusplit_o_bus_rsp_rdata[IFUSPLITTARGETNUM];
REG8 ifutransacFIFO_clked[IFUSPLIFIFODEPTH];
REG8 ifutransacFIFO_widx_clked;
REG8 ifutransacFIFO_ridx_clked;

BIT ifusplit_i_bus_cmd_valid;
BIT ifusplit_i_bus_cmd_ready;
BIT ifusplit_i_bus_cmd_read;
REG32 ifusplit_i_bus_cmd_adr;
REG32 ifusplit_i_bus_cmd_data;
REG8 ifusplit_i_bus_cmd_rwbyte;
BIT ifusplit_i_bus_rsp_valid;
BIT ifusplit_i_bus_rsp_ready;
REG32 ifusplit_i_bus_rsp_rdata;
REG8 ifutransacFIFO;
REG8 ifutransacFIFO_wid;
REG8 ifutransacFIFO_rid;
BIT ifutransacFIFO_wen;
REG8 ifutransacFIFO_widx;
BIT ifutransacFIFO_ren;
REG8 ifutransacFIFO_ridx;
BIT ifutransacFIFOempty;
BIT ifutransacFIFOfull;
BIT real_ifusplit_i_bus_cmd_valid;
REG8 nxtwrapped_ifutransacFIFO_widx;
BIT ifu2biu_cmd_valid;
BIT ifu2biu_cmd_ready;
BIT ifu2biu_cmd_read;
REG32 ifu2biu_cmd_adr;
REG32 ifu2biu_cmd_data;
REG8 ifu2biu_cmd_rwbyte;
BIT ifu2biu_rsp_valid;
BIT ifu2biu_rsp_ready;
REG32 ifu2biu_rsp_rdata;

BIT ifu2itcm_cmd_valid;
BIT ifu2itcm_cmd_ready;
BIT ifu2itcm_cmd_read;
REG32 ifu2itcm_cmd_adr;
REG32 ifu2itcm_cmd_data;
REG8 ifu2itcm_cmd_rwbyte;
BIT ifu2itcm_rsp_valid;
BIT ifu2itcm_rsp_ready;
REG32 ifu2itcm_rsp_rdata;

#endif //IFUBUSSPLIT_H