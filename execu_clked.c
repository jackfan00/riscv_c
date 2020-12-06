#include "execu.h"
#include "decode.h"
#include "memwb.h"

void execu_clked()
{
    int i;

if (!memwb_stall){
 exe_res_clked        = exe_res;
 exe_csr_res_clked    = csr_res;
 exe_rdidx_clked      = dec_rdidx_clked;
 exe_csridx_clked      = dec_csridx_clked;

 //exe_aluload_clked    = dec_aluload_clked;
 //exe_lh_clked        = dec_aluop_lh_clked;
 //exe_lhu_clked        = dec_aluop_lhu_clked;
 //exe_lb_clked        = dec_aluop_lb_clked;
 //exe_lbu_clked        = dec_aluop_lbu_clked;
 //exe_lw_clked        = dec_aluop_lw_clked;
 exe_dec_ilg_clked   = dec_dec_ilg_clked & (!exe_stall);
 exe_mulh_fuse_clked = dec_mulh_fuse_clked & (!exe_stall);
 lsu_load_misaligned_clked = lsu_load_misaligned & (!exe_stall);
 lsu_store_misaligned_clked = lsu_store_misaligned & (!exe_stall);
 lsu_misaligned_adr_clked = lsu_load_misaligned|lsu_store_misaligned ? lsu_cmd_adr : lsu_misaligned_adr_clked;
 exe_aluop_ecall_clked = dec_aluop_ecall_clked & (!exe_stall);
 exe_aluop_break_clked = dec_aluop_break_clked & (!exe_stall);
 exe_csr_wen_clked    = dec_csr_wen_clked & (!exe_stall);
 exe_csr_ren_clked    = dec_csr_ren_clked & (!exe_stall);
 exe_rden_clked       = exe_rden & (!exe_stall);
 exe_res_valid_clked  = exe_res_valid & (!exe_stall);
 exe_IR_clked = dec_IR_clked & (!exe_stall) ;
 exe_mret_clked = dec_aluop_mret_clked & (!exe_stall) ;
 //ras stack push
 //JAL/JALR can not back-to-back, must seprate 3 instruction apart, because of pipeline issue.
 if (dec_ras_push_clked){
     for (i=RASDEPTH-1;i<=1;i--){
         ras_stack[i] = ras_stack[i-1];
     }
     ras_stack[0] = exe_res;
 }

}

}
