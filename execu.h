 #ifndef EXECU_H
 #define EXECU_H

 #include "reg.h"

    //input
    BIT exe_res_valid_clked;
    REG32 exe_res_clked      ;
    BIT exe_rden_clked      ;
    BIT exe_rdidx_clked     ;
    BIT exe_aluload_clked;
    BIT exe_lh_clked;
    BIT exe_lhu_clked;
    BIT exe_lb_clked;
    BIT exe_lbu_clked;
    BIT exe_lw_clked;
    BIT exe_dec_ilg_clked;
    BIT lsu2mem_rsp_valid;
    BIT lsu2mem_rsp_ready;
    BIT lsu2mem_rsp_err;
    REG32 lsu2mem_rsp_rdata;

    //output 
    BIT exe_res_valid;
    REG32 exe_res           ;
    BIT lsu_stall;
    BIT lsu_misaligned;
    BIT lsu2mem_cmd_valid;
    BIT lsu2mem_cmd_ready;
    BIT lsu2mem_cmd_read;
    REG32 lsu2mem_cmd_adr;
    REG32 lsu2mem_cmd_wdata;
    REG8 lsu2mem_cmd_rwbyte;
    BIT exe_branch_pdict_fail;
    BIT exe_rden;
    REG32 exe_branch_pdict_fail_pc;
    BIT exe_jalr_pdict_fail;
    REG32 exe_jalr_pc;
    BIT mul_cmd_valid;
    REG32 mul_cmd_opd1;
    REG32 mul_cmd_opd2;
    REG8 mul_cmd_opmode;
    BIT div_cmd_valid;
    REG32 div_cmd_opd1;
    REG32 div_cmd_opd2;
    REG8 div_cmd_opmode;

#endif  //EXECU_H
