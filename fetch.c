//
#include "reg.h"
#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"
#include "opcode_define.h"
#include "ext_write_coderam.h"
#include "csrreg.h"

REG32 rv16torv32(REG16 in16);

//REG32 toir32 (REG16 ir16)
//{
// return 0;
//}

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

    opcode = firstinst_clked ? OPCODE_JAL : localIR & 0x7f;
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
    //JALR target address predict by RAS stack pop    
    //not calculate actual address, reduce hardware complexity and cost
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

    // need a one ADDER to predict BRANCH and JAL address
    branchjmp_pc = firstinst_clked ? BOOTADDR : 
                   fet_ras_pop ? (ras_stack[0]&0x0fffffff)+ITCM_ADDR_BASE :  //ensure valid code address
                   alu_opd1 + alu_opd2;

}

void fetch()
{

//local


    //fetch_stall=0;
    fetch_stall =  (exe_stall) | (dec_stall) | (memwb_stall) | (csr_exception_stall); // & ifu_rsp_valid;
    //codebus_connect();

    //stalled_ifu_rsp_valid = !fetch_stall_clked ? ifu_rsp_valid : ifu_rsp_valid_clked;
    stalled_ifu_rsp_valid = ifu_rsp_valid | ifu_rsp_valid_clked;

    //instruction from code-ram
    ifu_rsp_ready = 1; //(!fetch_stall) & (!exe_stall) & (!dec_stall) & (!memwb_stall) & (!csr_exception_stall); // & ifu_rsp_valid;
    //
    //
    buffered_rsp_rdata = ifu_rsp_valid&ifu_rsp_ready ? ifu_rsp_rdata : buffered_rsp_rdata_clked;
    //memIR = stalled_ifu_rsp_valid&ifu_rsp_ready ? ifu_rsp_rdata : buffered_rsp_rdata_clked ;
    memIR = buffered_rsp_rdata; //ifu_rsp_rdata;
    memIR_hi16 = stalled_ifu_rsp_valid & ifu_rsp_ready ? (buffered_rsp_rdata>>16) & 0x0ffff : memIR_hi16_clked;

    //
    memIR16 =   //branchjmp ? ((fetpc_clked&0x02) == 0 ? memIR & 0x0ffff : (memIR>>16) & 0x0ffff) :
                (fetpc_clked&0x02) == 0 ? memIR & 0x0ffff : memIR_hi16_clked; // (memIR>>16) & 0x0ffff;
    // calculate next pc
    irlsb10 = memIR16 & 0x03; //(fetpc_clked&0x02) == 0 ? memIR & 0x03 :  (memIR>>16) & 0x03;
    fet_ir16 = (stalled_ifu_rsp_valid&ifu_rsp_ready)|(remain_ir16s_clked==2) ? irlsb10!=3 : fet_ir16_clked;
    //fet_ir16 = irlsb10!=3;
    if (fet_ir16){
        memIR32 = rv16torv32(memIR16);
    }
    else{
        memIR32 = (fetpc_clked&0x02) == 0 ? memIR : ((memIR&0x0ffff) << 16) + memIR_hi16_clked;
    }
    iroffset = fet_ir16 ? 2 : 4;
    //mini deocde for branchjmp
    //fetdec(memIR32);
    fetdec(fetchIR);
    //merge exception to jmp signal control
    branchjmp_pc = csr_exception_flush ? csrtrappc : branchjmp_pc;
    branchjmp = branchjmp | csr_exception_flush;

    //
    // this paramter use for calculate remain_ir16s: (number of instructions which not consume yet)
    remain_ir16s =  downloadstart|downloadper_clked? 0://remain_ir16s_clked:
                    exe_branch_pdict_fail|exe_jalr_pdict_fail|branchjmp ? (nxtpc&0x02 ? -1 : 0) :
                    remain_ir16s_clked - 
                    //in negative case or flush, doesnt cousume ir. 
                    ((remain_ir16s_clked>>7)|fetch_flush ? 0 : (fet_ir16?1:2)) + 
                    (stalled_ifu_rsp_valid & ifu_rsp_ready?2:0);
    //jmp instr & ifu fetch instr stall condition
    //in the next cycle need to hold nxtpc no change
    pcjmpconi = (exe_branch_pdict_fail|exe_jalr_pdict_fail|branchjmp) & ifu_stall;
    pcjmpconi = pcjmpconi ? 1 : 
                !ifu_stall ? 0 : pcjmpconi_clked;
    //
    nxtpc = csr_exception_flush   ? branchjmp_pc :  //1st priority
            exe_branch_pdict_fail ? exe_branch_pdict_fail_pc :
            exe_jalr_pdict_fail ? exe_jalr_pc :
            branchjmp   ? branchjmp_pc : 
            fetpc_clked + (pcjmpconi_clked ? 0 :iroffset);
            //fetch_stall ? fetpc_clked : fetpc_clked + iroffset;
            //ifu2mem_cmd_ready ? fetpc_clked + iroffset : fetpc_clked;

    //req new instr when remain ir16 count less than 2
    ifu_cmd_valid = downloadstart|downloadper_clked|fetch_stall? 0: ((remain_ir16s<=1)|(remain_ir16s>>7));

    //ifu_cmd_adr change
    ifu_cmd_adr =   (remain_ir16s>>7) ? nxtpc :
                    (ifu_cmd_adr_clked&0xfffffffc) == (nxtpc&0xfffffffc) ? nxtpc+2 : nxtpc;
    ifu_cmd_adr = ifu_cmd_adr & 0xfffffffc;
    
    //ifu_stall use to keep fetch stage instr not change
    //but need to flush some instr, doing flush at decode stage
    //to avoid converge issue(combinational loop)
    ifu_stall = ifu_cmd_valid & (!ifu_cmd_ready);
   
    //for pc_keep_clked period, its pc is not changed.
    pc_keep = (remain_ir16s==0xff) ? 1 :
                (ifu_cmd_valid & ifu_cmd_ready) ? 0 : pc_keep_clked;
    pc =    // these conditions is always update new pc , 1st priority
            (exe_branch_pdict_fail|exe_jalr_pdict_fail|branchjmp)           ? nxtpc :   

    //to keep ifu_cmd_adr no change because of ifu_cmd_ready not ready (ifu_stall condition) 
            pc_keep_clked|ifu_stall ? fetpc_clked :
    //for remain_ir16s_clked value is negative cycle, its pc is invalid dont update.
         (ifu_cmd_valid & (remain_ir16s>=0) & ifu_cmd_ready & (!(remain_ir16s_clked>>7)) ) | 
         (remain_ir16s==2 ) ? nxtpc : 
         //(exe_branch_pdict_fail|exe_jalr_pdict_fail|branchjmp)           ? nxtpc : 
         fetpc_clked;

    //to keep ifu_cmd_adr no change because of ifu_cmd_ready not ready 
    //pc = ifu_stall ?     fetpc_clked : pc;

    //
    fetch_flush =(!(  stalled_ifu_rsp_valid & ifu_rsp_ready  )) & (remain_ir16s_clked!=2);  
    //to avoid flush at ifu_stall period, 
    fetch_flush = fetch_flush | csr_exception_flush;  

    fetch_flush = fetch_flush | exe_branch_pdict_fail | exe_jalr_pdict_fail | 
                                 (remain_ir16s_clked>>7); //remain_ir16s_clked is negative means jmpto address[1:0]==10
                                                          //need take 2 cycles to get full instruntion
    //fetch_flush = fetch_flush  & (!fetch_stall);                                                     
    fetchIR =  fetch_flush  ?  NOP : memIR32;

    //
    ifu_cmd_read =1;
    ifu_cmd_rwbyte = 0xf;


}


