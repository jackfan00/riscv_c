#include "execu.h"
#include "decode.h"
#include "memwb.h"
#include "csrreg.h"
#include "opcode_define.h"

void execu_clked()
{
    int i;

if ((!memwb_stall) && (!csr_exception_stall)){
    exe_validir_d1_clked       = exe_validir_clked & (!exe_stall) & (!csr_exception_flush);
 exe_pc_d1_clked            = exe_pc_clked;
 exe_ir16_d1_clked             = exe_ir16_clked;
 //exe_pc_clked               = decpc_clked;
//
 exe_res_clked              = exe_res;
 exe_csr_res_clked          = csr_res;
 exe_rdidx_clked            = dec_rdidx_clked;
 exe_csridx_clked           = dec_csridx_clked;
 //exe_IR_clked               = exe_stall|csr_exception_flush ? NOP : raw_dec_IR;//dec_IR_clked       ;
 exe_IR_d1_clked            = exe_IR_clked;
 exe_IR_clked               = raw_dec_IR;
 exe_bjir_d1_clked          = exe_bjir_clked;
 exe_bjir_clked             = (alubranch|alujalr|alujal);
//
// exe_ir16_clked             = dec_ir16_clked        & (!exe_stall) & (!csr_exception_flush);
 exe_dec_ilg_clked          = dec_dec_ilg_clked     & (!exe_stall) & (!csr_exception_flush);
 exe_mulh_fuse_clked        = dec_mulh_fuse_clked   & (!exe_stall) & (!csr_exception_flush);
 lsu_load_misaligned_clked  = lsu_load_misaligned   & (!exe_stall) & (!csr_exception_flush);
 lsu_store_misaligned_clked = lsu_store_misaligned  & (!exe_stall) & (!csr_exception_flush);
 exe_aluop_ecall_clked      = dec_aluop_ecall_clked & (!exe_stall) & (!csr_exception_flush);
 exe_aluop_break_clked      = dec_aluop_break_clked & (!exe_stall) & (!csr_exception_flush);
 exe_csr_wen_clked          = dec_csr_wen_clked     & (!exe_stall) & (!csr_exception_flush);
 exe_csr_ren_clked          = dec_csr_ren_clked     & (!exe_stall) & (!csr_exception_flush);
 exe_rden_clked             = exe_rden              & (!exe_stall) & (!csr_exception_flush);
 exe_res_valid_clked        = exe_res_valid         & (!exe_stall) & (!csr_exception_flush);
 exe_mret_clked             = dec_aluop_mret_clked  & (!exe_stall) & (!csr_exception_flush);
 lsu_misaligned_adr_clked   = lsu_load_misaligned|lsu_store_misaligned ? lsu_cmd_adr : lsu_misaligned_adr_clked;
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
