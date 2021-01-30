#ifndef EXTBUSSPLIT_H
#define EXTBUSSPLIT_H
void extbussplit();
void extbussplit_clked();

#include "reg.h"


//last target dont need to compare targetbase
REG32 extsplit_o_bus_cmd_data[EXTSPLITTARGETNUM];
REG8 extsplit_TARGETBASE[EXTSPLITTARGETNUM];  //MSB
BIT extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM];
BIT extsplit_o_bus_cmd_ready[EXTSPLITTARGETNUM];
BIT extsplit_o_bus_cmd_read[EXTSPLITTARGETNUM];
REG8 extsplit_o_bus_cmd_rwbyte[EXTSPLITTARGETNUM];
REG32 extsplit_o_bus_cmd_adr[EXTSPLITTARGETNUM];
BIT extsplit_o_bus_rsp_valid[EXTSPLITTARGETNUM];
BIT extsplit_o_bus_rsp_ready[EXTSPLITTARGETNUM];
BIT extsplit_o_bus_rsp_read[EXTSPLITTARGETNUM];
REG32 extsplit_o_bus_rsp_rdata[EXTSPLITTARGETNUM];
REG8 exttransacFIFO_clked[EXTSPLIFIFODEPTH];
REG8 extregfileidxFIFO_clked[EXTSPLIFIFODEPTH];
BIT extregfilerdenFIFO_clked[EXTSPLIFIFODEPTH];
REG8 exttransacFIFO_widx_clked;
REG8 exttransacFIFO_ridx_clked;

BIT extsplit_i_bus_cmd_valid;
BIT extsplit_i_bus_cmd_ready;
BIT extsplit_i_bus_cmd_read;
REG8 extsplit_i_bus_cmd_rwbyte;
REG32 extsplit_i_bus_cmd_adr;
REG32 extsplit_i_bus_cmd_data;
BIT extsplit_i_bus_rsp_valid;
BIT extsplit_i_bus_rsp_ready;
BIT extsplit_i_bus_rsp_read;
REG32 extsplit_i_bus_rsp_rdata;
REG8 extsplit_i_bus_rsp_regidx;
BIT extsplit_i_bus_rsp_rden;
REG8 exttransacFIFO;
REG8 extregfileidxFIFO;
BIT extregfilerdenFIFO;
REG8 exttransacFIFO_wid;
REG8 exttransacFIFO_rid;
BIT exttransacFIFO_wen;
REG8 exttransacFIFO_widx;
BIT exttransacFIFO_ren;
REG8 exttransacFIFO_ridx;
BIT exttransacFIFOempty;
BIT exttransacFIFOfull;
BIT real_extsplit_i_bus_cmd_valid;
REG8 nxtwrapped_exttransacFIFO_widx;
BIT ext2biu_cmd_valid;
BIT ext2biu_cmd_ready;
BIT ext2biu_cmd_read;
REG32 ext2biu_cmd_adr;
REG32 ext2biu_cmd_data;
REG8 ext2biu_cmd_rwbyte;
BIT ext2biu_rsp_valid;
BIT ext2biu_rsp_ready;
BIT ext2biu_rsp_read;
REG32 ext2biu_rsp_rdata;

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

BIT ext2itcm_cmd_valid;
BIT ext2itcm_cmd_ready;
BIT ext2itcm_cmd_read;
REG32 ext2itcm_cmd_adr;
REG32 ext2itcm_cmd_data;
REG8 ext2itcm_cmd_rwbyte;
BIT ext2itcm_rsp_valid;
BIT ext2itcm_rsp_ready;
BIT ext2itcm_rsp_read;
REG32 ext2itcm_rsp_rdata;

#endif //EXTBUSSPLIT_H