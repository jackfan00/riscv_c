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

#endif // MEMWB_H
