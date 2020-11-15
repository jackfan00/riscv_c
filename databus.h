#ifndef MEMORYBUS_H
#define MEMORYBUS_H
#include "reg.h"

//input
BIT i_databus_grt_clked[CODEARBIT_NUM];
BIT i_databus_cmd_valid[CODEARBIT_NUM];
BIT i_databus_cmd_read[CODEARBIT_NUM];
REG32 i_databus_cmd_adr[CODEARBIT_NUM];
REG32 i_databus_cmd_wdata[CODEARBIT_NUM];
REG8 i_databus_cmd_rwbyte[CODEARBIT_NUM];
BIT o_databus_cmd_ready;
BIT data_rspid_fifo_full_clked;
BIT data_rspid_fifo_empty_clked;
REG8 r_data_rspid;
BIT o_databus_rsp_valid;
BIT o_databus_rsp_err;
REG32 o_databus_rsp_rdata;
BIT i_databus_rsp_ready[CODEARBIT_NUM];
REG32 data_rspid_fifo_wadr_clked;
REG32 data_rspid_fifo_radr_clked;
REG32 dataram_rdat;
BIT dataram_cs_clked;
BIT dataram_we_clked;
BIT dataram_wrsp_per_clked;
BIT dataram_rrsp_per_clked;

// output
BIT i_databus_grt[CODEARBIT_NUM];
BIT o_databus_cmd_valid;
BIT o_databus_cmd_read;
REG32 o_databus_cmd_adr;
REG32 o_databus_cmd_wdata;
REG8 o_databus_cmd_rwbyte;
BIT i_databus_cmd_ready[CODEARBIT_NUM];
BIT data_rspid_fifo_wen;
BIT data_rspid_fifo_ren;
BIT i_databus_rsp_valid[CODEARBIT_NUM];
BIT i_databus_rsp_err[CODEARBIT_NUM];
REG32 i_databus_rsp_rdata[CODEARBIT_NUM];
BIT o_databus_rsp_ready;
REG8 w_data_rspid;
REG32 data_rspid_fifo_wadr;
REG32 data_rspid_fifo_radr;
REG32 dataram_adr;
BIT dataram_cs;
REG32 dataram_wdat;
BIT dataram_we;
REG8 dataram_bmask;
BIT dataram_wrsp_valid;
BIT dataram_rrsp_valid;

// for simulate purpose, not hardware requirement
int dataram_ready_cycles_clked;


#endif // MEMORYBUS_H
