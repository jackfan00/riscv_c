#ifndef FETCH_H
#define FETCH_H
void fetch();
void fetch_clked();

#include "reg.h"
//input
BIT fetch_stall;
REG16 memIR_hi16_clked;
BIT fetch_flush;
REG32 fetchIR_clked;
REG32 fetpc_clked;
REG32 flush_pc;
BIT ifu_cmd_ready;
REG32 rs1v;
BIT branchjmp_hipart_clked;
BIT new_midnxtpc_part2_fg_clked;
BIT fet_rs1en_ack;
REG32 fet_rs1v;
BIT fet_predict_jmp_clked;
BIT fet_ir16_clked;
BIT firstinst_clked;
REG8 remain_ir16s_clked;
REG32 ifu_cmd_adr_clked;
REG16 fetchIR16_clked;
REG32 buffered_rsp_rdata_clked;
BIT ifu_rsp_valid_clked;
BIT fetch_stall_clked;

//output
BIT stalled_ifu_rsp_valid;
BIT ifu_rsp_valid;
REG32 ifu_rsp_rdata;
BIT ifu_rsp_ready;
BIT ifu_rsp_read;
BIT ifu_cmd_valid;
BIT ifu_cmd_read;
REG32 ifu_cmd_adr;
REG8 ifu_cmd_rwbyte;
BIT branchjmp;
BIT predict_en;
BIT fet_predict_jmp;
REG32 branchjmp_pc;
BIT fet_rs1en;
REG8 fet_rs1idx;
REG8 fet_rdidx;
BIT branchjmp_hipart;
BIT new_midnxtpc_part2_fg;
BIT fet_ras_pop;
BIT fet_ir16;
REG8 remain_ir16s;
REG16 memIR_hi16;
REG32 fetchIR;
REG32 pc;
REG32 memIR;
REG32 memIR32;
REG16 memIR16;
REG8 irlsb10;
REG8 iroffset;
REG32 nxtpc;
REG32 buffered_rsp_rdata;

//BIT ddd;
//BIT ddd1;
//BIT ddd2;
//BIT ddd3;
#endif // FETCH_H

