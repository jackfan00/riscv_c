#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"

void decode_clked()
{
    //
    // dependence RAW check
    //if (rden){
    //    depfifo[depfifo_wadr_clked]    = rdidx;
    //    depfifo_fg[depfifo_wadr_clked] = 1;
    //    depfifo_wadr_clked = depfifo_wadr_clked>=(DEPFIFOSIZE-1) ? 0 : depfifo_wadr_clked+1;
    //}


if ((!lsu_stall) && (!memwb_stall)){
 decpc_clked = fetpc_clked;
    // for store command, need
 dec_rs2v_clked       = real_rs2v;
    //
 dec_alu_opd1_clked   = alu_opd1;
 dec_alu_opd2_clked   = alu_opd2;
 dec_rs1idx_clked     = rs1idx;
 dec_rs2idx_clked     = rs2idx;
 dec_rdidx_clked      = rdidx;
 dec_rs1en_clked      = rs1en;
 dec_rs2en_clked      = rs2en;
 dec_rden_clked       = rden     & (!dec_stall);
 dec_aluop_sub_clked  = aluop_sub;
 dec_aluop_add_clked  = aluop_add;
 dec_aluop_sll_clked  = aluop_sll;
 dec_aluop_slt_clked  = aluop_slt;
 dec_aluop_sltu_clked = aluop_sltu;
 dec_aluop_xor_clked  = aluop_xor;
 dec_aluop_sra_clked  = aluop_sra;
 dec_aluop_srl_clked  = aluop_srl;
 dec_aluop_or_clked   = aluop_or;
 dec_aluop_and_clked  = aluop_and;
 dec_dec_ilg_clked    = dec_ilg  & (!dec_stall);
 dec_aluopimm_clked   = aluopimm;
 dec_aluop_clked      = aluop;
 dec_aluload_clked    = aluload  & (!dec_stall);
 dec_alustore_clked   = alustore & (!dec_stall);
 dec_alujal_clked     = alujal;
 dec_alujalr_clked    = alujalr;
 dec_alului_clked     = alului;
 dec_aluauipc_clked   = aluauipc;
 dec_alubranch_clked  = alubranch & (!dec_stall);
 dec_alumiscmem_clked = alumiscmem;
 dec_alusystem_clked  = alusystem;
 dec_aluop_beq_clked  = aluop_beq;
 dec_aluop_bne_clked  = aluop_bne;
 dec_aluop_blt_clked  = aluop_blt;
 dec_aluop_bge_clked  = aluop_bge;
 dec_aluop_bltu_clked = aluop_bltu;
 dec_aluop_bgeu_clked = aluop_bgeu;
 dec_aluop_lb_clked   = aluop_lb;
 dec_aluop_lh_clked   = aluop_lh;
 dec_aluop_lw_clked   = aluop_lw;
 dec_aluop_lbu_clked  = aluop_lbu;
 dec_aluop_lhu_clked  = aluop_lhu;
 dec_aluop_sb_clked   = aluop_sb;
 dec_aluop_sh_clked   = aluop_sh;
 dec_aluop_sw_clked   = aluop_sw;
 dec_aluop_mul_clked   = aluop_mul;
 dec_aluop_mulh_clked   = aluop_mulh;
 dec_aluop_mulhsu_clked   = aluop_mulhsu;
 dec_aluop_mulhu_clked   = aluop_mulhu;
 dec_aluop_div_clked   = aluop_div;
 dec_aluop_divu_clked   = aluop_divu;
 dec_aluop_rem_clked   = aluop_rem;
 dec_aluop_remu_clked   = aluop_remu;
 dec_ras_push_clked   = dec_ras_push;
 dec_predict_jmp_clked = fet_predict_jmp_clked;
 cti_pc_clked          = cti_pc;
 dec_jalr_pdict_fail_clked = dec_jalr_pdict_fail & (!dec_stall);
}

}
