#include "execu.h"
#include "decode.h"
#include "mul.h"
#include "lsubussplit.h"
#include "lif.h"
#include "regfilemerge.h"

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
    REG32 set_res;
    REG32 clr_res;
    REG32 csrw_res;
    BIT dtcmsel;
    BIT plicsel;


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

    set_res = or_res;
    clr_res = and_res;
    csrw_res = dec_alu_opd1_clked;


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

              //csr operation, for ecall and breakcase , rden will be 0
              //dec_alu_opd2_clked is put old csrvalue, write to rd
              dec_alusystem_clked ? dec_alu_opd2_clked :  
              0;

    csr_res = dec_aluop_csrset_clked ? set_res :
              dec_aluop_csrclr_clked ? clr_res :
              dec_aluop_csrw_clked   ? csrw_res : 
              dec_alu_opd2_clked;  //mret's mepc reg value

    //LSU generation
    //normal itcm/dtcm load will not have lif_loadfull condition
    //only may happen at BIU bus target peripheral/flash access
    lsu_cmd_valid = (dec_aluload_clked& (!lif_loadfull)) | dec_alustore_clked; // & exe_res_valid & (!lsu_misaligned); 
    lsu_cmd_read = dec_aluload_clked;
    lsu_cmd_adr = exe_res;
    lsu_cmd_data = dec_rs2v_clked;
    lsu_cmd_rwbyte = dec_aluop_lw_clked | dec_aluop_sw_clked ? 0xf :
                         dec_aluop_lh_clked | dec_aluop_lhu_clked | dec_aluop_sh_clked ? 0x3 : 0x1;

    //
    //when lsu load command, the rsp will be sent to regfile
    //so rsp_ready is from lsu2regfile_cmd_ready
    lsu_rsp_ready = (!lsu_rsp_read ? 1 : lsu2regfile_cmd_ready) ;//& lsu_rsp_valid ;                     
    //additional info , use for rsp write to regfile, 
    //need busfifo (lsubussplit) store these info
    lsu_cmd_regidx =  dec_rdidx_clked;  
    lsu_cmd_rden = dec_aluload_clked;
    //
    //lsu2regfile 
    lsu2regfile_cmd_valid = lsu_rsp_valid & lsu_rsp_read & lsu_rsp_rden;
    lsu2regfile_cmd_read = 0;
    lsu2regfile_cmd_adr = lsu_rsp_regidx;
    lsu2regfile_cmd_data = lsu_rsp_rdata;
    lsu2regfile_cmd_rwbyte = 0xf;
    lsu2regfile_rsp_ready = 1;

    //
    lsu_stall = lsu_cmd_valid & (!lsu_cmd_ready);        
    lsu_load_misaligned = (dec_aluload_clked ) & (
                     (((lsu_cmd_adr&0x03)!=0) & lsu_cmd_rwbyte==0xf) | (((lsu_cmd_adr&0x03)==3) & lsu_cmd_rwbyte!=0x1)
                    );
    lsu_store_misaligned = ( dec_alustore_clked) & (
                     (((lsu_cmd_adr&0x03)!=0) & lsu_cmd_rwbyte==0xf) | (((lsu_cmd_adr&0x03)==3) & lsu_cmd_rwbyte!=0x1)
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

    mul_rsp_ready = mul2regfile_cmd_ready ;//& mul_rsp_valid;                     
    //mul2regfile 
    //mul dedicate for execu, no others use it
    //and produce result at fixed 2 cycles
    mul_cmd_regidx =  exe_rdidx_clked;  
    mul_cmd_rden = exe_rden_clked;
    //
    mul2regfile_cmd_valid = mul_rsp_valid & mul_rsp_rden;
    mul2regfile_cmd_read = 0;
    mul2regfile_cmd_adr = mul_rsp_regidx;
    mul2regfile_cmd_data = mul_rsp_rdata;
    mul2regfile_cmd_rwbyte = 0xf;
    mul2regfile_rsp_ready = 1;


    div_cmd_valid = dec_aluop_div_clked | dec_aluop_divu_clked | dec_aluop_rem_clked | dec_aluop_remu_clked;
    div_cmd_opd1 = dec_alu_opd1_clked;
    div_cmd_opd2 = dec_alu_opd2_clked;
    div_cmd_opmode = dec_aluop_div_clked + (dec_aluop_divu_clked<<1) + (dec_aluop_rem_clked<<2)+(dec_aluop_remu_clked<<3);
    div_stall = div_cmd_valid & (!div_cmd_ready);

    div_rsp_ready = div2regfile_cmd_ready ;//& div_rsp_valid;                     
    //need to store these info for futher use
    //because div cycle is not fixed and may longer than 2 
    div_cmd_regidx = dec_rdidx_clked;  
    div_cmd_rden   = dec_rden_clked;
    //
    //div2regfile 
    div2regfile_cmd_valid = div_rsp_valid & div_rsp_rden;
    div2regfile_cmd_read = 0;
    div2regfile_cmd_adr =  div_rsp_regidx;
    div2regfile_cmd_data = div_rsp_rdata;
    div2regfile_cmd_rwbyte = 0xf;
    div2regfile_rsp_ready = 1;

    //lif: long instrution flag
    //write to lif after commit load-command
    lif_loadrdidx = lsu_cmd_valid & lsu_cmd_ready & lsu_cmd_read ? dec_rdidx_clked :
                      regfile_wrload ?  0 : lif_loadrdidx_clked;

    lif_divrdidx = div_cmd_valid & div_cmd_ready ? dec_rdidx_clked : 
                      regfile_wrdiv ?  0 : lif_divrdidx_clked;
    //lif already contain value
    //div no need to do lif_divfull condition, because only 1 div target                  
    lif_loadfull = (lif_loadrdidx_clked!=0) & (!regfile_wrload) ;

    exe_stall = mul_stall | div_stall | lsu_stall;
    
}
