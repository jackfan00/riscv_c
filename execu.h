 #ifndef EXECU_H
 #define EXECU_H

 #include "reg.h"

    //output
    BIT exe_res_valid;
    BIT exe_res_valid_clked;
    REG32 exe_res           ;
    REG32 exe_res_clked      ;
    BIT exe_rden_clked      ;
    BIT exe_rdidx_clked     ;
    BIT lsu_stall;
    BIT lsu_misaligned;
    BIT lsu2mem_cmd_valid;
    BIT lsu2mem_cmd_ready;
    BIT lsu2mem_cmd_read;
    REG32 lsu2mem_cmd_adr;
    REG32 lsu2mem_cmd_wdata;
    REG8 lsu2mem_cmd_rwbyte;
    BIT lsu2mem_rsp_valid;
    BIT lsu2mem_rsp_ready;
    BIT lsu2mem_rsp_err;
    REG32 lsu2mem_rsp_rdata;
    BIT exe_branch_pdict_fail;
    BIT exe_rden;
    REG32 exe_branch_pdict_fail_pc;
    BIT exe_jalr_pdict_fail;
    REG32 exe_jalr_pc;

#endif  //EXECU_H
