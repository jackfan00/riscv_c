#ifndef BIUBUSSPLIT_H
#define BIUBUSSPLIT_H
#include "reg.h"


//last target dont need to compare targetbase
REG8 biusplit_TARGETBASE[BIUSPLITTARGETNUM];  //MSB

BIT biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM];
BIT biusplit_o_bus_cmd_ready[BIUSPLITTARGETNUM];
BIT biusplit_o_bus_cmd_read[BIUSPLITTARGETNUM];
REG32 biusplit_o_bus_cmd_adr[BIUSPLITTARGETNUM];
REG32 biusplit_o_bus_cmd_data[BIUSPLITTARGETNUM];
REG8 biusplit_o_bus_cmd_rwbyte[BIUSPLITTARGETNUM];
BIT biusplit_o_bus_rsp_valid[BIUSPLITTARGETNUM];
BIT biusplit_o_bus_rsp_ready[BIUSPLITTARGETNUM];
REG32 biusplit_o_bus_rsp_rdata[BIUSPLITTARGETNUM];
REG8 biutransacFIFO_clked[BIUSPLIFIFODEPTH];
REG8 biutransacFIFO_widx_clked;
REG8 biutransacFIFO_ridx_clked;

BIT biusplit_i_bus_cmd_valid;
BIT biusplit_i_bus_cmd_ready;
BIT biusplit_i_bus_cmd_read;
REG32 biusplit_i_bus_cmd_adr;
REG32 biusplit_i_bus_cmd_data;
REG8 biusplit_i_bus_cmd_rwbyte;
BIT biusplit_i_bus_rsp_valid;
BIT biusplit_i_bus_rsp_ready;
REG32 biusplit_i_bus_rsp_rdata;
REG8 biutransacFIFO;
REG8 biutransacFIFO_wid;
REG8 biutransacFIFO_rid;
BIT biutransacFIFO_wen;
REG8 biutransacFIFO_widx;
BIT biutransacFIFO_ren;
REG8 biutransacFIFO_ridx;
BIT biutransacFIFOempty;
BIT biutransacFIFOfull;
BIT real_biusplit_i_bus_cmd_valid;
REG8 nxtwrapped_biutransacFIFO_widx;


#endif //BIUBUSSPLIT_H