#ifndef FETCH_H
#define FETCH_H
#include "reg.h"
//input
BIT fetch_stall;
BIT ifu2mem_rsp_valid;
REG32 ifu2mem_rsp_rdata;
REG16 memIR_hi16_clked;
BIT fetch_flush;
REG32 fetchIR_clked;
REG32 fetpc_clked;
REG32 flush_pc;
BIT ifu2mem_cmd_ready;
REG32 rs1v;
BIT branchjmp_hipart_clked;
BIT new_midnxtpc_part2_fg_clked;
BIT fet_rs1en_ack;
REG32 fet_rs1v;

//output
BIT ifu2mem_rsp_ready;
REG16 memIR_hi16;
REG32 fetchIR;
REG32 pc;
BIT ifu2mem_cmd_valid;
BIT ifu2mem_cmd_read;
REG32 ifu2mem_cmd_adr;
REG8 ifu2mem_cmd_rwbyte;
BIT branchjmp;
BIT predict_en;
BIT predict_jmp;
REG32 branchjmp_pc;
BIT fet_rs1en;
REG8 fet_rs1idx;
BIT branchjmp_hipart;
BIT new_midnxtpc_part2_fg;

#endif // FETCH_H

