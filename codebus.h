#ifndef MEMORYBUS_H
#define MEMORYBUS_H
#include "reg.h"

//input
BIT i_codebus_grt_clked[CODEARBIT_NUM];
BIT i_codebus_cmd_valid[CODEARBIT_NUM];
BIT i_codebus_cmd_read[CODEARBIT_NUM];
REG32 i_codebus_cmd_adr[CODEARBIT_NUM];
REG32 i_codebus_cmd_wdata[CODEARBIT_NUM];
REG8 i_codebus_cmd_rwbyte[CODEARBIT_NUM];
BIT o_codebus_cmd_ready;
BIT code_rspid_fifo_full_clked;
BIT code_rspid_fifo_empty_clked;
REG8 r_code_rspid;
BIT o_codebus_rsp_valid;
BIT o_codebus_rsp_err;
REG32 o_codebus_rsp_rdata;
BIT i_codebus_rsp_ready[CODEARBIT_NUM];
REG32 code_rspid_fifo_wadr_clked;
REG32 code_rspid_fifo_radr_clked;
REG32 coderam_rdat;
BIT coderam_cs_clked;
BIT coderam_we_clked;

// output
BIT i_codebus_grt[CODEARBIT_NUM];
BIT o_codebus_cmd_valid;
BIT o_codebus_cmd_read;
REG32 o_codebus_cmd_adr;
REG32 o_codebus_cmd_wdata;
REG8 o_codebus_cmd_rwbyte;
BIT i_codebus_cmd_ready[CODEARBIT_NUM];
BIT code_rspid_fifo_wen;
BIT code_rspid_fifo_ren;
BIT i_codebus_rsp_valid[CODEARBIT_NUM];
BIT i_codebus_rsp_err[CODEARBIT_NUM];
REG32 i_codebus_rsp_rdata[CODEARBIT_NUM];
BIT o_codebus_rsp_ready;
REG8 w_code_rspid;
REG32 code_rspid_fifo_wadr;
REG32 code_rspid_fifo_radr;
REG32 coderam_adr;
BIT coderam_cs;
REG32 coderam_wdat;
BIT coderam_we;
REG8 coderam_bmask;
BIT coderam_wrsp_per_clked;
BIT coderam_rrsp_per_clked;
BIT coderam_wrsp_valid;
BIT coderam_rrsp_valid;

// for simulate purpose, not hardware requirement
int ready_cycles_clked;

//normal sram parameter is  (1, 0)
#define CODERAM_RREADY_CYCLES 3
#define CODERAM_WREADY_CYCLES 0

#endif // MEMORYBUS_H
