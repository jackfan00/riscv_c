#include "execu.h"
#include "decode.h"
#include "memwb.h"

void execu_clked()
{
    int i;

if (!memwb_stall){
 exe_res_clked        = exe_res;
 exe_res_valid_clked  = exe_res_valid;
 exe_rden_clked       = exe_rden;
 exe_rdidx_clked      = dec_rdidx_clked;
 //exe_aluload_clked    = dec_aluload_clked;
 //exe_lh_clked        = dec_aluop_lh_clked;
 //exe_lhu_clked        = dec_aluop_lhu_clked;
 //exe_lb_clked        = dec_aluop_lb_clked;
 //exe_lbu_clked        = dec_aluop_lbu_clked;
 //exe_lw_clked        = dec_aluop_lw_clked;
 exe_dec_ilg_clked   = dec_dec_ilg_clked & (!exe_stall);
 exe_mulh_fuse_clked = dec_mulh_fuse_clked & (!exe_stall);

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
