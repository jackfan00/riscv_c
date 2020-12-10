 #ifndef EXECU_H
 #define EXECU_H

 #include "reg.h"

    //input
    BIT exe_ir16_clked;
    REG32 exe_pc_clked;
    REG32 lsu_misaligned_adr_clked;
    BIT exe_aluop_ecall_clked;
    BIT exe_aluop_break_clked;
    BIT lsu_load_misaligned_clked;
    BIT lsu_store_misaligned_clked;
    BIT exe_res_valid_clked;
    REG32 exe_res_clked      ;
    BIT exe_rden_clked      ;
    REG8 exe_rdidx_clked     ;
    BIT exe_aluload_clked;
    BIT exe_lh_clked;
    BIT exe_lhu_clked;
    BIT exe_lb_clked;
    BIT exe_lbu_clked;
    BIT exe_lw_clked;
    BIT exe_dec_ilg_clked;
    BIT lsu_rsp_valid;
    BIT lsu_rsp_read;
    BIT lsu_rsp_ready;
    BIT lsu_rsp_rden;
    REG8 lsu_rsp_regidx;
    //BIT lsu_rsp_err;
    REG32 lsu_rsp_rdata;
    BIT exe_mulh_fuse_clked;
    BIT exe_csr_wen_clked;
    BIT exe_csr_ren_clked;
    REG16 exe_csridx_clked;
    REG32 exe_csr_res_clked;
    REG32 exe_IR_clked;
    BIT exe_mret_clked;

    //output 
    BIT exe_res_valid;
    REG32 exe_res ;
    REG32 csr_res;
    BIT exe_stall;
    BIT lsu_load_misaligned;
    BIT lsu_store_misaligned;
    BIT lsu_cmd_valid;
    BIT dtcm_cmd_valid;
    //BIT plic_cmd_valid;
    BIT lsu_cmd_ready;
    BIT dtcm_cmd_ready;
    BIT plic_cmd_ready;
    BIT lsu_cmd_read;
    REG32 lsu_cmd_adr;
    REG32 lsu_cmd_data;
    REG8 lsu_cmd_rwbyte;
    REG8 lsu_cmd_regidx;
    BIT lsu_cmd_rden;
    BIT exe_branch_pdict_fail;
    BIT exe_rden;
    REG32 exe_branch_pdict_fail_pc;
    BIT exe_jalr_pdict_fail;
    REG32 exe_jalr_pc;

    BIT mul_cmd_valid;
    BIT mul_cmd_ready;
    REG32 mul_cmd_opd1;
    REG32 mul_cmd_opd2;
    REG8 mul_cmd_opmode;
    REG8 mul_cmd_regidx;
    BIT mul_cmd_rden;
    BIT mul_rsp_valid;
    BIT mul_rsp_read;
    REG32 mul_rsp_rdata;
    REG8 mul_rsp_regidx;
    BIT mul_rsp_rden;

    BIT div_cmd_valid;
    REG32 div_cmd_opd1;
    REG32 div_cmd_opd2;
    REG8 div_cmd_opmode;
    BIT div_cmd_ready;
    REG8 div_cmd_regidx;
    BIT div_cmd_rden;
    BIT div_rsp_valid;
    BIT div_rsp_ready;
    BIT div_rsp_read;
    REG32 div_rsp_rdata;
    BIT div_rsp_rden;
    REG8 div_rsp_regidx;


    BIT mul2regfile_cmd_valid;
    BIT mul2regfile_cmd_ready;
    BIT mul2regfile_cmd_read;
    REG32 mul2regfile_cmd_adr;
    REG32 mul2regfile_cmd_data;
    REG8 mul2regfile_cmd_rwbyte;
    BIT mul2regfile_rsp_valid;
    BIT mul2regfile_rsp_ready;
    BIT mul2regfile_rsp_read;
    REG32 mul2regfile_rsp_rdata;

    BIT div2regfile_cmd_valid;
    BIT div2regfile_cmd_ready;
    BIT div2regfile_cmd_read;
    REG32 div2regfile_cmd_adr;
    REG32 div2regfile_cmd_data;
    REG8 div2regfile_cmd_rwbyte;
    BIT div2regfile_rsp_valid;
    BIT div2regfile_rsp_ready;
    BIT div2regfile_rsp_read;
    REG32 div2regfile_rsp_rdata;


    BIT lsu2regfile_cmd_valid;
    BIT lsu2regfile_cmd_ready;
    BIT lsu2regfile_cmd_read;
    REG32 lsu2regfile_cmd_adr;
    REG32 lsu2regfile_cmd_data;
    REG8 lsu2regfile_cmd_rwbyte;
    BIT lsu2regfile_rsp_valid;
    BIT lsu2regfile_rsp_ready;
    BIT lsu2regfile_rsp_read;
    REG32 lsu2regfile_rsp_rdata;

    BIT exe_branch_taken;
    BIT lsu_stall;
    BIT mul_stall;
    BIT div_stall;
    BIT lif_loadfull;

#endif  //EXECU_H
