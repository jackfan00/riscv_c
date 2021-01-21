#ifndef MEMWB_H
#define MEMWB_H
void memwb();

#include "reg.h"

BIT memwb_bjir;
BIT memwb_validir;
REG32 memwb_pc;
BIT memwb_ir16;
REG8 memwb_idx;
BIT memwb_valid;
BIT memwb_ready;
BIT memwb_stall;
REG8 lsu2mem_rsp_adr;

//REG32 div_rsp_rdata;
//REG8 div_rsp_adr;
BIT mul_rsp_valid;
BIT mul_rsp_ready;
//REG32 mul_rsp_rdata;
REG8 mul_rsp_adr;
REG8 memwb_id;
BIT memwb_dec_ilg;
BIT memwb_load_misaligned;
BIT memwb_store_misaligned;
BIT memwb_ecall;
BIT memwb_break;
REG32 memwb_lsu_misaligned_adr;
REG32 memwb_IR;
BIT memwb_excephappen;
BIT memwb_mret;
REG16 csrreg_adr;
REG32 csrreg_wdata;
BIT csrreg_wen;
BIT csrreg_ren;

BIT memwb2regfile_cmd_valid;
BIT memwb2regfile_cmd_ready;
BIT memwb2regfile_cmd_read;
REG32 memwb2regfile_cmd_adr;
REG32 memwb2regfile_cmd_data;
REG8 memwb2regfile_cmd_rwbyte;
BIT memwb2regfile_rsp_valid;
BIT memwb2regfile_rsp_ready;
BIT memwb2regfile_rsp_read;
REG32 memwb2regfile_rsp_rdata;
BIT memwb2regfile_stall;

#endif // MEMWB_H
