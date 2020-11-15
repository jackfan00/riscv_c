#include "execu.h"
#include "decode.h"

void execu()
{
    //local
    long long addsub_res, opd1_longlong, exeop1, exeop2;
    BIT exeop_sub;
    BIT exeop_unsigned;
    REG8 shamt;
    //REG32 exeop2;
    REG32 slt_res;
    REG32 xor_res;
    REG32 eq_res;
    REG32 or_res;
    REG32 and_res;
    REG32 sll_res;
    REG32 srl_res;
    REG32 sra_res;
    BIT exe_branch_taken;

    int tmp1, tmp2;




    exeop_sub = dec_aluop_sub_clked | dec_aluop_slt_clked | dec_aluop_sltu_clked | dec_alubranch_clked;
    exeop_unsigned = dec_aluop_sltu_clked | dec_aluop_bltu_clked | dec_aluop_bgeu_clked;
    //exeop2 = exeop_sub ? ~dec_alu_opd2_clked : dec_alu_opd2_clked;
    //addsub_res = dec_alu_opd1_clked + exeop2 + exeop_sub;
    //should change to hardware implementation method
    tmp1 = (int) dec_alu_opd1_clked;
    tmp2 = (int) dec_alu_opd2_clked;
    exeop1 = exeop_unsigned ? dec_alu_opd1_clked : ((long long)tmp1);
    exeop2 = exeop_unsigned ? dec_alu_opd2_clked : ((long long)tmp2);
    exeop2 = exeop_sub ? ~exeop2 : exeop2;
    addsub_res = exeop1 + exeop2 + exeop_sub ;

    slt_res = (addsub_res<0);
    xor_res = dec_alu_opd1_clked ^ dec_alu_opd2_clked;
    eq_res = xor_res==0;

    or_res = dec_alu_opd1_clked | dec_alu_opd2_clked;
    and_res = dec_alu_opd1_clked & dec_alu_opd2_clked;

    // should merge to shift-left in hardware to reduce cost
    shamt = dec_alu_opd2_clked & 0x1f;
    sll_res = dec_alu_opd1_clked << shamt;
    srl_res = dec_alu_opd1_clked >> shamt;
    opd1_longlong = dec_alu_opd1_clked;
    sra_res = opd1_longlong >> shamt;

    //
    exe_res_valid = 1;//!exe_branch_pdict_fail;
    exe_res = (dec_aluop_sub_clked|dec_aluop_add_clked|dec_alujal_clked|dec_alujalr_clked|dec_alului_clked|dec_aluauipc_clked|dec_aluload_clked|dec_alustore_clked) ? (REG32)addsub_res :
              (dec_aluop_sll_clked) ? sll_res :
              (dec_aluop_srl_clked) ? srl_res :
              (dec_aluop_sra_clked) ? sra_res :
              (dec_aluop_slt_clked|dec_aluop_sltu_clked) ? slt_res :
              (dec_aluop_xor_clked) ? xor_res :
              (dec_aluop_or_clked) ? or_res :
              (dec_aluop_and_clked) ? and_res :
              (dec_aluop_beq_clked) ? eq_res :
              (dec_aluop_bne_clked) ? !eq_res :
              (dec_aluop_blt_clked | dec_aluop_bltu_clked) ? slt_res :
              (dec_aluop_bge_clked | dec_aluop_bgeu_clked) ? !slt_res : 0;

    //
    lsu2mem_cmd_valid = (dec_aluload_clked | dec_alustore_clked) & exe_res_valid & (!lsu_misaligned);
    lsu2mem_cmd_read = dec_aluload_clked;
    lsu2mem_cmd_adr = exe_res;
    lsu2mem_cmd_wdata = dec_rs2v_clked;
    lsu2mem_cmd_rwbyte = dec_aluop_lw_clked | dec_aluop_sw_clked ? 0xf :
                         dec_aluop_lh_clked | dec_aluop_lhu_clked | dec_aluop_sh_clked ? 0x3 : 0x1;

    lsu_stall = lsu2mem_cmd_valid & (!lsu2mem_cmd_ready);        
    lsu_misaligned = (dec_aluload_clked | dec_alustore_clked) & (
                     (((lsu2mem_cmd_adr&0x03)!=0) & lsu2mem_cmd_rwbyte==0xf) | (((lsu2mem_cmd_adr&0x03)==3) & lsu2mem_cmd_rwbyte!=0x1)
                    );
    exe_branch_taken = (dec_aluop_beq_clked & eq_res) | (dec_aluop_bne_clked & (!eq_res)) | 
                       ((dec_aluop_blt_clked | dec_aluop_bltu_clked) & slt_res) |
                       ((dec_aluop_bge_clked | dec_aluop_bgeu_clked) & (!slt_res));
    exe_branch_pdict_fail = dec_alubranch_clked & (exe_branch_taken ^ dec_predict_jmp_clked);  

    exe_branch_pdict_fail_pc = cti_pc_clked ;

    exe_jalr_pc = cti_pc_clked;

    exe_jalr_pdict_fail = dec_jalr_pdict_fail_clked;
                                                
    exe_rden =  lsu_stall ? 0 : dec_rden_clked;

}
