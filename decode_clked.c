#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"
#include "csrreg.h"
#include "lif.h"
#include "opcode_define.h"

void decode_clked()
{
    //
    // dependence RAW check
    //if (rden){
    //    depfifo[depfifo_wadr_clked]    = rdidx;
    //    depfifo_fg[depfifo_wadr_clked] = 1;
    //    depfifo_wadr_clked = depfifo_wadr_clked>=(DEPFIFOSIZE-1) ? 0 : depfifo_wadr_clked+1;
    //}


if ((!exe_stall) && (!memwb_stall) && (!csr_exception_stall)){
 //decpc_clked = fetpc_clked;
 exe_pc_clked               = decpc_clked;
 exe_ir16_clked             = dec_ir16_clked;
 exe_validir_clked          = dec_validir_clked & (!dec_stall) &(!csr_exception_flush);// & (!ifu_stall);
    // for store command, need
 dec_rs2v_clked       = real_rs2v;
    //
 dec_alu_opd1_clked   = alu_opd1;
 dec_alu_opd2_clked   = alu_opd2;
 dec_rs1idx_clked     = rs1idx;
 dec_rs2idx_clked     = rs2idx;
 dec_rdidx_clked      = rdidx;
 dec_aluop_add_clked  = aluop_add; 
 dec_aluopimm_clked   = aluopimm;

 lif_divrdidx_clked   = lif_divrdidx_flush  ? 0 : lif_divrdidx ;// & (!dec_stall) ;
 lif_loadrdidx_clked  = lif_loadrdidx_flush ? 0 : lif_loadrdidx;// & (!dec_stall) &(!csr_exception_flush);

 dec_rs1en_clked      = rs1en                    & (!dec_stall) &(!csr_exception_flush);
 dec_rs2en_clked      = rs2en                    & (!dec_stall) &(!csr_exception_flush);
 dec_rden_clked       = rden                     & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sub_clked  = aluop_sub                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sll_clked  = aluop_sll                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_slt_clked  = aluop_slt                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sltu_clked = aluop_sltu               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_xor_clked  = aluop_xor                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sra_clked  = aluop_sra                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_srl_clked  = aluop_srl                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_or_clked   = aluop_or                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_and_clked  = aluop_and                & (!dec_stall) &(!csr_exception_flush);
 dec_dec_ilg_clked    = dec_ilg                  & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_clked      = aluop                    & (!dec_stall) &(!csr_exception_flush);
 dec_aluload_clked    = aluload                  & (!dec_stall) &(!csr_exception_flush);
 dec_alustore_clked   = alustore                 & (!dec_stall) &(!csr_exception_flush);
 dec_alujal_clked     = alujal                   & (!dec_stall) &(!csr_exception_flush);
 dec_alujalr_clked    = alujalr                  & (!dec_stall) &(!csr_exception_flush);
 dec_alului_clked     = alului                   & (!dec_stall) &(!csr_exception_flush);
 dec_aluauipc_clked   = aluauipc                 & (!dec_stall) &(!csr_exception_flush);
 dec_alubranch_clked  = alubranch                & (!dec_stall) &(!csr_exception_flush);
 dec_alumiscmem_clked = alumiscmem               & (!dec_stall) &(!csr_exception_flush);
 dec_alusystem_clked  = alusystem                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_beq_clked  = aluop_beq                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_bne_clked  = aluop_bne                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_blt_clked  = aluop_blt                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_bge_clked  = aluop_bge                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_bltu_clked = aluop_bltu               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_bgeu_clked = aluop_bgeu               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_lb_clked   = aluop_lb                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_lh_clked   = aluop_lh                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_lw_clked   = aluop_lw                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_lbu_clked  = aluop_lbu                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_lhu_clked  = aluop_lhu                & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sb_clked   = aluop_sb                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sh_clked   = aluop_sh                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_sw_clked   = aluop_sw                 & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_mul_clked   = aluop_mul               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_mulh_clked   = aluop_mulh             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_mulhsu_clked   = aluop_mulhsu         & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_mulhu_clked   = aluop_mulhu           & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_div_clked   = aluop_div               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_divu_clked   = aluop_divu             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_rem_clked   = aluop_rem               & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_remu_clked   = aluop_remu             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_csrset_clked = aluop_csrset           & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_csrclr_clked = aluop_csrclr           & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_ecall_clked = aluop_ecall             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_break_clked = aluop_break             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_csrw_clked = aluop_csrw               & (!dec_stall) &(!csr_exception_flush);
 dec_csr_wen_clked = dec_csr_wen                 & (!dec_stall) &(!csr_exception_flush);
 dec_csr_ren_clked = dec_csr_ren                 & (!dec_stall) &(!csr_exception_flush);
 dec_ras_push_clked   = dec_ras_push             & (!dec_stall) &(!csr_exception_flush);
 dec_jalr_pdict_fail_clked = dec_jalr_pdict_fail & (!dec_stall) &(!csr_exception_flush);
 dec_mulh_fuse_clked = dec_mulh_fuse             & (!dec_stall) &(!csr_exception_flush);
 dec_aluop_mret_clked = aluop_mret               & (!dec_stall) &(!csr_exception_flush);
 dec_predict_jmp_clked = fet_predict_jmp_clked   & (!dec_stall) &(!csr_exception_flush);
 dec_csridx_clked = csridx;
 cti_pc_clked          = cti_pc;
 branch_taken_pc_clked = branch_taken_pc;
 //use for mtval
 //dec_IR_clked = fet_ir16_clked ? (dec_stall ? NOP : fetchIR16_clked ) : 
 //                                (dec_stall ? NOP : fetchIR_clked   ) ;
 //dec_ir16_clked = fet_ir16_clked;
}

}
