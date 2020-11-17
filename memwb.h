#ifndef MEMWB_H
#define MEMWB_H

#include "reg.h"

REG32 memwb_wdata;
REG8 memwb_idx;
BIT memwb_valid;
BIT memwb_ready;
BIT memwb_stall;
BIT lsu2mem_rsp_valid;
BIT lsu2mem_rsp_ready;
REG32 lsu2mem_rsp_rdata;
REG8 lsu2mem_rsp_adr;
BIT div_rsp_valid;
BIT div_rsp_ready;
REG32 div_rsp_rdata;
REG8 div_rsp_adr;
BIT mul_rsp_valid;
BIT mul_rsp_ready;
REG32 mul_rsp_rdata;
REG8 mul_rsp_adr;

#endif // MEMWB_H
