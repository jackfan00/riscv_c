//
#include "reg.h"
#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"
#include "opcode_define.h"

REG32 toir32 (REG16 ir16)
{
 return 0;
}

void fetdec(REG32 localIR)
{
REG32 opcode;
REG32 i_imm;
REG32 b_imm;
REG32 j_imm;
int s_i_imm;
int s_b_imm;
int s_j_imm;
REG32 alu_opd1;
int alu_opd2;
BIT fet_raw_dec_rs1;
BIT fet_raw_exe_rs1;
BIT fet_raw_memwb_rs1;
REG32 fet_real_rs1v;
BIT fet_rdlink;
BIT fet_rs1link;

    opcode = firstclk ? OPCODE_JAL : localIR & 0x7f;
    fet_rdidx =  (localIR >> 7) & 0x1f;
    fet_rs1idx = (localIR >> 15) & 0x1f;
    fet_rdlink = (fet_rdidx==1) || (fet_rdidx==5);
    fet_rs1link = (fet_rs1idx==1) || (fet_rs1idx==5);
    i_imm = (localIR >> 20) & 0xfff;  ///**< signed value */
    b_imm = (((localIR>>31)&0x1) << 12 ) +  (((localIR>>7)&0x1) << 11 ) + (((localIR>>25)&0x3f) << 5 ) + (((localIR>>8)&0xf) << 1 );
    j_imm = (((localIR>>31)&0x1) << 20 ) +  (((localIR>>12)&0xff) << 12 ) + (((localIR>>20)&0x1) << 11 ) + (((localIR>>21)&0x3ff) << 1 );
    s_i_imm = (i_imm > 0x7ff) ? i_imm - 4096 : i_imm ;
    s_b_imm = (b_imm >=(1<<12)) ? b_imm - (1<<13) : b_imm;
    s_j_imm = (j_imm >=(1<<20)) ? j_imm - (1<<21) : j_imm;

    fet_rs1en =0;
    switch(opcode)
    {
    case OPCODE_JAL:
        alu_opd1 = fetpc_clked;
        alu_opd2 = s_j_imm;
        //
        branchjmp =1;
        break;
    case OPCODE_JALR:
    //    alu_opd1 = fet_real_rs1v;
    //    alu_opd2 = s_i_imm;
    //    fet_rs1en =1;
        //
        branchjmp =fet_ras_pop;
        break;
    case OPCODE_BRANCH:
        alu_opd1 = fetpc_clked;
        alu_opd2 = s_b_imm;
        fet_predict_jmp= s_b_imm<0 ? 1 : 0;
        branchjmp =fet_predict_jmp;
        break;
    default:
        branchjmp =0;
        break;
    }

    //fet_raw_dec_rs1   =   (rden             & (rdidx          ==fet_rs1idx && fet_rs1en));
    //fet_raw_exe_rs1   =   (dec_rden_clked   & (dec_rdidx_clked==fet_rs1idx && fet_rs1en));
    //fet_raw_memwb_rs1 =   (exe_rden_clked   & (exe_rdidx_clked==fet_rs1idx && fet_rs1en));

    //fet_real_rs1v =  
    //                fet_raw_exe_rs1   ? exe_res :
    //                fet_raw_memwb_rs1 ? memwb_wdata : fet_rs1v;
    //fetch_stall = (fet_rs1en & (!fet_rs1en_ack)) | fet_raw_dec_rs1;

    //ras_push = (opcode==OPCODE_JAL  & (fet_rdidx==1 || fet_rdidx==5)) |
    //           (opcode==OPCODE_JALR & (fet_rdidx==1 || fet_rdidx==5) & (fet_rs1idx!=1 && fet_rs1idx!=5)) |
    //           (opcode==OPCODE_JALR & (fet_rdidx==1 || fet_rdidx==5) & (fet_rs1idx==1 || fet_rs1idx==5)) ;
    fet_ras_pop =  (opcode==OPCODE_JALR & (!fet_rdlink) & (fet_rs1link)) |
         (opcode==OPCODE_JALR & (fet_rdlink) & (fet_rs1link) & (fet_rdidx!=fet_rs1idx)) ;

    branchjmp_pc = firstclk ? BOOTADDR : 
                   fet_ras_pop ? (ras_stack[0]&0x0fffffff)+ITCM_ADDR_BASE :  //ensure valid code address
                   alu_opd1 + alu_opd2;

}

void fetch()
{

//local
REG32 memIR;
REG32 memIR32;
REG16 memIR16;
REG8 irlsb10;
BIT nxtir16;
REG8 iroffset;
REG32 nxtpc;
BIT newir_fg;
BIT ifu2mem_cmd_valid_nor;
REG32 ifu2mem_cmd_adr_nor;
BIT ifu2mem_cmd_valid_bj;
BIT incpc_valid;
BIT midnxtpc_fg;
BIT new_midnxtpc_fg;

    //
    fetch_stall=0;
    codebus_connect();

    //instruction from code-ram
    ifu2mem_rsp_ready = !fetch_stall;
    //memIR = ifu2mem_rsp_valid & ifu2mem_rsp_ready ? ifu2mem_rsp_rdata : 0;
    memIR = ifu2mem_rsp_rdata ;
    memIR_hi16 = ifu2mem_rsp_valid & ifu2mem_rsp_ready ? (ifu2mem_rsp_rdata>>16) & 0x0ffff : memIR_hi16_clked;

    //mini deocde for branchjmp
    fetdec(memIR);
    //
    memIR16 = (fetpc_clked&0x02) == 0 ? memIR & 0x0ffff :  (memIR>>16) & 0x0ffff;
    // calculate next pc
    irlsb10 = (fetpc_clked&0x02) == 0 ? memIR & 0x03 :  (memIR>>16) & 0x03;
    fet_ir16 = irlsb10!=3;
    if (fet_ir16){
        memIR32 = toir32(memIR16);
    }
    else{
        memIR32 = (fetpc_clked&0x02) == 0 ? memIR : ((memIR&0x0ffff) << 16) + memIR_hi16_clked;
    }
    iroffset = fet_ir16 ? 2 : 4;

    //
    nxtpc = exe_branch_pdict_fail ? exe_branch_pdict_fail_pc :
            exe_jalr_pdict_fail ? exe_jalr_pc :
            branchjmp   ? branchjmp_pc : fetpc_clked + iroffset;
            //fetch_stall ? fetpc_clked : fetpc_clked + iroffset;
            //ifu2mem_cmd_ready ? fetpc_clked + iroffset : fetpc_clked;

    newir_fg =  (fetpc_clked&0xfffffffc)!=(nxtpc&0xfffffffc) ;
    midnxtpc_fg = (nxtpc&0x02);
    new_midnxtpc_fg = newir_fg & midnxtpc_fg ;
    new_midnxtpc_part2_fg = new_midnxtpc_fg & ifu2mem_cmd_ready;

    ifu2mem_cmd_valid = (newir_fg | midnxtpc_fg | new_midnxtpc_part2_fg_clked) & (!fetch_stall);
    ifu2mem_cmd_adr = newir_fg | new_midnxtpc_fg ? nxtpc :
                      midnxtpc_fg | new_midnxtpc_part2_fg_clked ? nxtpc + 0x02 : 0;

    pc = ifu2mem_cmd_valid & (!new_midnxtpc_part2_fg_clked) & ifu2mem_cmd_ready ? nxtpc : fetpc_clked;

    fetch_flush =!(  ifu2mem_rsp_valid & ifu2mem_rsp_ready &(!new_midnxtpc_part2_fg_clked) );
    fetch_flush = fetch_flush | exe_branch_pdict_fail | exe_jalr_pdict_fail;
    fetchIR =  fetch_flush ?  NOP : memIR32;

    //
    //nxtir16 = (nxtpc&0x02) ?  ((memIR>>16)& 0x03)!=3 : (memIR & 0x03)!=3;
    //ifu2mem_cmd_valid_nor =  newir_fg ? 1 :
    //                        !nxtir16 ? 1 : 0;
    //ifu2mem_cmd_adr_nor =  nxtpc + (nxtpc&0x03) ;  //normal continue fetch

    //branchjmp case: jmp to not align 4-byte address, need fetch 2 times

    //branchjmp_hipart = branchjmp_hipart_clked ? !ifu2mem_cmd_ready : branchjmp & ((branchjmp_pc&0x03)!=0) & ifu2mem_cmd_ready;
    //ifu2mem_cmd_valid_bj = branchjmp | branchjmp_hipart_clked;
    //ifu2mem_cmd_valid = (ifu2mem_cmd_valid_nor | ifu2mem_cmd_valid_bj) & !fetch_stall;
    //ifu2mem_cmd_adr = ifu2mem_cmd_valid_nor ? ifu2mem_cmd_adr_nor :
    //                  branchjmp ? nxtpc :
    //                  branchjmp_hipart_clked ? nxtpc+2 : 0;
    ifu2mem_cmd_read =1;
    ifu2mem_cmd_rwbyte = 0xf;

    //incpc_valid = ifu2mem_cmd_valid_nor | (branchjmp & ((branchjmp_pc&0x03)==0)) | (branchjmp_hipart_clked & ((branchjmp_pc&0x03)!=0));
    //pc = incpc_valid & ifu2mem_cmd_ready ? nxtpc : fetpc_clked;

}


