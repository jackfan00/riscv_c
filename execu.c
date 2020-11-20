#include "execu.h"
#include "decode.h"
#include "mul.h"

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
    BIT lsu_stall;
    BIT mul_stall;
    BIT div_stall;

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
    //stall case                                        
    exe_rden =  exe_stall ? 0 : dec_rden_clked;
    exe_res_valid = div_cmd_valid | (mul_cmd_valid & (MUL_RSPVALID_CYCLES>0)) | dec_aluload_clked  ? 0 : 1;

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
              (dec_aluop_bge_clked | dec_aluop_bgeu_clked) ? !slt_res : 
              //(mul_cmd_valid & (MUL_RSPVALID_CYCLES==0)) ? mulres :   //single cycle multiple hardware
              0;

    //LSU generation
    lsu2mem_cmd_valid = (dec_aluload_clked | dec_alustore_clked); // & exe_res_valid & (!lsu_misaligned); 
    lsu2mem_cmd_read = dec_aluload_clked;
    lsu2mem_cmd_adr = exe_res;
    lsu2mem_cmd_wdata = dec_rs2v_clked;
    lsu2mem_cmd_rwbyte = dec_aluop_lw_clked | dec_aluop_sw_clked ? 0xf :
                         dec_aluop_lh_clked | dec_aluop_lhu_clked | dec_aluop_sh_clked ? 0x3 : 0x1;

    // continue load command will stall
    lsu_stall = lsu2mem_cmd_valid & (!lsu2mem_cmd_ready);        
    lsu_misaligned = (dec_aluload_clked | dec_alustore_clked) & (
                     (((lsu2mem_cmd_adr&0x03)!=0) & lsu2mem_cmd_rwbyte==0xf) | (((lsu2mem_cmd_adr&0x03)==3) & lsu2mem_cmd_rwbyte!=0x1)
                    );

    //branch/jalr judgement                
    exe_branch_taken = (dec_aluop_beq_clked & eq_res) | (dec_aluop_bne_clked & (!eq_res)) | 
                       ((dec_aluop_blt_clked | dec_aluop_bltu_clked) & slt_res) |
                       ((dec_aluop_bge_clked | dec_aluop_bgeu_clked) & (!slt_res));
    exe_branch_pdict_fail = dec_alubranch_clked & (exe_branch_taken ^ dec_predict_jmp_clked);  
    exe_branch_pdict_fail_pc = cti_pc_clked ;
    exe_jalr_pc = cti_pc_clked;
    exe_jalr_pdict_fail = dec_jalr_pdict_fail_clked;        

    

    //RV32M
    mul_cmd_valid = //dec_mulh_fuse_clked ? 0 :
                    dec_aluop_mul_clked | dec_aluop_mulh_clked | dec_aluop_mulhsu_clked | dec_aluop_mulhu_clked;
    mul_cmd_opd1 = dec_alu_opd1_clked;
    mul_cmd_opd2 = dec_alu_opd2_clked;
    mul_cmd_opmode = dec_aluop_mul_clked + (dec_aluop_mulh_clked<<1) + (dec_aluop_mulhsu_clked<<2)+(dec_aluop_mulhu_clked<<3);
    mul_stall = mul_cmd_valid & (!mul_cmd_ready);

    div_cmd_valid = dec_aluop_div_clked | dec_aluop_divu_clked | dec_aluop_rem_clked | dec_aluop_remu_clked;
    div_cmd_opd1 = dec_alu_opd1_clked;
    div_cmd_opd2 = dec_alu_opd2_clked;
    div_cmd_opmode = dec_aluop_div_clked + (dec_aluop_divu_clked<<1) + (dec_aluop_rem_clked<<2)+(dec_aluop_remu_clked<<3);
    div_stall = div_cmd_valid & (!div_cmd_ready);

    exe_stall = mul_stall | div_stall | lsu_stall;
    
}
