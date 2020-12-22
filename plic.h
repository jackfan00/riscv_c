#ifndef PLIC_H
#define PLIC_H
void plic();
void plic_clked();

#include "reg.h"

#define PLIC_PRIORITY_BASE  0x0c000000
#define PLIC_IP_BASE        0x0c001000
#define PLIC_IE_BASE        0x0c002000
#define PLIC_PRI_THRESHOLD  0x0c200000
#define PLIC_CLAIMCOMPLETE  0x0c200004

//input
BIT intsource_clked[PLIC_INTNUMBER];
REG32 IE_clked[PLIC_INTNUMBER_REG32];
REG32 IP_clked[PLIC_INTNUMBER_REG32];
BIT EIP_clked;
REG8 INTID_clked;
REG8 prioritythreshold_clked;
REG8 priority_clked[PLIC_INTNUMBER];
BIT gateway_enable_clked[PLIC_INTNUMBER];
BIT plic_read_clked;
REG32 plic_regradr_clked;
BIT plic_write_clked;
BIT plic_read1st_clked;
REG32 read_plic_rdat_clked;
REG32 plic_csadr_clked;

//output
BIT ccw;
BIT ccr;
BIT intsource[PLIC_INTNUMBER];
REG8 priorityout[PLIC_INTNUMBER];
REG8 maxid[PLIC_INTNUMBER];
BIT IP[PLIC_INTNUMBER];
BIT EIP;
REG8 INTID;
REG8 prioritythreshold;
BIT ie[PLIC_INTNUMBER];
REG8 priority[PLIC_INTNUMBER];
BIT plic_regcs;
BIT plic_regw;
REG32 plic_regwdata;
REG32 plic_regadr;
REG32 plic_regrdata;
BIT plic_cmd_valid;
BIT plic_cmd_ready;
BIT plic_cmd_read;
REG32 plic_cmd_adr;
REG32 plic_cmd_data;
BIT plic_rsp_valid;
BIT plic_rsp_ready;
BIT plic_rsp_read;
REG32 plic_rsp_rdata;
BIT plic_read;
REG32 plic_regwadr;
REG32 plic_regradr;
REG32 plic_rdat;
BIT plic_write;
BIT plic_read1st;
REG32 read_plic_rdat;

#endif //PLIC_H