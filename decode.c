#include <stdio.h>
#include "opcode_define.h"
#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "memwb.h"


void decodeinit()
{
 rs1en=0;
 rs2en=0;
 rden=0;
 aluop_sub=0;
 aluop_add=0;
 aluop_sll=0;
 aluop_slt=0;
 aluop_sltu=0;
 aluop_xor=0;
 aluop_sra=0;
 aluop_srl=0;
 aluop_or=0;
 aluop_and=0;
 dec_ilg=0;
 aluopimm=0;
 aluop=0;
 aluload=0;
 alustore=0;
 alujal=0;
 alujalr=0;
 alului=0;
 aluauipc=0;
 alubranch=0;
 alumiscmem=0;
 alusystem=0;
 aluop_beq=0;
 aluop_bne=0;
 aluop_blt=0;
 aluop_bge=0;
 aluop_bltu=0;
 aluop_bgeu=0;

}

void decode()
{
//local
BIT dec_flush;
REG32 dec_IR;
BIT dec_raw_exe_rs1;
BIT dec_raw_exe_rs2;
BIT dec_raw_memwb_rs1;
BIT dec_raw_memwb_rs2;
REG8 opcode;
REG8 func3;
REG8 func7;
//REG8 shamt;
BIT func7_20;
BIT func7_00;
BIT rs1x0;
BIT rs2x0;
BIT rdx0;
REG32 i_imm;
REG32 s_imm;
REG32 b_imm;
REG32 u_imm;
REG32 j_imm;
REG32 cti_pc_op1;
REG32 cti_pc_op2;

int s_i_imm;
int s_s_imm;
int s_b_imm;
int s_j_imm;

//
    decodeinit();
    //
    dec_flush = exe_branch_pdict_fail | exe_jalr_pdict_fail;
    dec_IR = dec_flush ? NOP : fetchIR_clked;

    opcode = dec_IR & 0x7f;
    func3 = (dec_IR >> 12) & 0x07;
    func7 = (dec_IR >> 25) & 0x3f;
    rs1idx = (dec_IR >> 15) & 0x1f;
    rs2idx = (dec_IR >> 20) & 0x1f;
    i_imm = (dec_IR >> 20) & 0xfff;  //< signed value
    s_imm = (((dec_IR>>25)&0x7f) << 5 ) +  ((dec_IR>>7)&0x1f)   ;
    b_imm = (((dec_IR>>31)&0x1) << 12 ) +  (((dec_IR>>7)&0x1) << 11 ) + (((dec_IR>>25)&0x3f) << 5 ) + (((dec_IR>>8)&0xf) << 1 );
    u_imm = (dec_IR & 0xfffff000);  ///< msb[31:12]
    j_imm = (((dec_IR>>31)&0x1) << 20 ) +  (((dec_IR>>12)&0xff) << 12 ) + (((dec_IR>>20)&0x1) << 11 ) + (((dec_IR>>21)&0x3ff) << 1 );
    rdidx = (dec_IR >> 7) & 0x1f;
    //shamt = rs2idx;
    rs1x0 = (rs1idx==0);
    rs2x0 = (rs2idx==0);
    rdx0 = (rdidx==0);
    //
    s_i_imm = (i_imm > 0x7ff) ? i_imm - 4096 : i_imm ;
    s_s_imm = (s_imm >=(1<<11)) ? s_imm - (1<<12) : s_imm;
    s_b_imm = (b_imm >=(1<<12)) ? b_imm - (1<<13) : b_imm;
    s_j_imm = (j_imm >=(1<<20)) ? j_imm - (1<<21) : j_imm;
    //
    func7_20 = (func7 == 0x20);
    func7_00 = (func7 == 0x00);

    switch(opcode)
    {
    case OPCODE_IMM:
        alu_opd1 = real_rs1v;
        alu_opd2 = s_i_imm;
        rs1en =!rs1x0;
        rs2en =0;
        rden = !rdx0;
        aluopimm =1;
        break;
    case OPCODE_OP:
        alu_opd1 = real_rs1v;
        alu_opd2 = real_rs2v;
        rs1en =!rs1x0;
        rs2en =!rs2x0;
        rden = !rdx0;
        aluop =1;
        break;
    case OPCODE_LOAD:
        alu_opd1 = real_rs1v;
        alu_opd2 = s_i_imm;
        rs1en =!rs1x0;
        rs2en =0;
        rden = !rdx0;
        aluload =1;
        break;
    case OPCODE_STORE:
        alu_opd1 = real_rs1v;
        alu_opd2 = s_s_imm;
        rs1en =!rs1x0;
        rs2en =!rs2x0;
        rden = 0;
        alustore =1;
        break;
    case OPCODE_LUI:
        alu_opd1 = 0;
        alu_opd2 = u_imm;
        rs1en =0;
        rs2en =0;
        rden = !rdx0;
        alului =1;
        break;
    case OPCODE_AUIPC:
        alu_opd1 = decpc_clked;
        alu_opd2 = u_imm;
        rs1en =0;
        rs2en =0;
        rden = !rdx0;
        aluauipc =1;
        break;
    case OPCODE_JAL:
        alu_opd1 = decpc_clked;
        alu_opd2 = 4;
        rs1en =0;
        rs2en =0;
        rden = !rdx0;
        alujal =1;
        //
        break;
    case OPCODE_JALR:
        alu_opd1 = decpc_clked;
        alu_opd2 = 4;
        rs1en =!rs1x0 ;
        rs2en =0;
        rden = !rdx0 ;
        alujalr =1;
        //
        break;
    case OPCODE_BRANCH:
        alu_opd1 = real_rs1v;
        alu_opd2 = real_rs2v;
        rs1en =!rs1x0;
        rs2en =!rs2x0;
        rden = 0;
        alubranch =1;
        break;
    case OPCODE_MISCMEM:
        alumiscmem =1;
        break;
    case OPCODE_SYSTEM:
        alusystem =1;
        break;
    default:
        printf("decode Error: not supported opcode %d \n", opcode);
        break;
    }
    //
    switch(func3)
    {
    //case ALU_ADD:
    case ALU_SUB:
        aluop_add = aluopimm | (aluop & func7_00);
        aluop_sub = (aluop & func7_20);
        dec_ilg = aluop  & (!aluopimm) & (!func7_20) & (!func7_00);
        //
        if (dec_ilg){
            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_SLL:
        aluop_sll = (aluop| aluopimm) & func7_00 ;
        dec_ilg = (aluop| aluopimm) & (!func7_00);

        if (dec_ilg){
            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_SLT:
            aluop_slt =(aluop & func7_00) | aluopimm;
            dec_ilg = aluop & (!aluopimm) & (!func7_00);

        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_SLTU:
            aluop_sltu =(aluop & func7_00) | aluopimm;
            dec_ilg = aluop & (!aluopimm) & (!func7_00);

        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_XOR:
            aluop_xor =(aluop & func7_00) | aluopimm;
            dec_ilg = aluop & (!aluopimm) & (!func7_00);
        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    //case ALU_SRL:
    case ALU_SRA:
            aluop_sra =(aluop|aluopimm) & func7_20;
            aluop_srl =(aluop|aluopimm) & func7_00;
            dec_ilg = (aluop|aluopimm) & (!func7_20) &(!func7_00);

        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_OR:
            aluop_or =(aluop & func7_00) | aluopimm;
            dec_ilg = aluop & (!aluopimm) & (!func7_00);
        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
        break;
    case ALU_AND:
            aluop_and =(aluop & func7_00) | aluopimm;
            dec_ilg = aluop & (!aluopimm) & (!func7_00);
        if (dec_ilg){

            printf("decode Error: illogical opcode %08x, at clockcnt =%d= \n", dec_IR, clockcnt);
        }
       break;

    }

    //

    switch(func3)
        {
        case BRANCH_BEQ:
            aluop_beq =alubranch;
            break;
        case BRANCH_BNE:
            aluop_bne =alubranch;

            break;
         case BRANCH_BLT:
            aluop_blt =alubranch;
            break;
         case BRANCH_BGE:
            aluop_bge =alubranch;
            break;
         case BRANCH_BLTU:
            aluop_bltu =alubranch;

            break;
         case BRANCH_BGEU:
            aluop_bgeu =alubranch;

            break;
         default:
            dec_ilg =alubranch;

            break;
       }

    switch(func3)
        {
        case LOAD_LB:
            aluop_lb =aluload;
            break;
        case LOAD_LH:
            aluop_lh =aluload;
            break;
         case LOAD_LW:
            aluop_lw =aluload;
            break;
         case LOAD_LBU:
            aluop_lbu =aluload;
            break;
         case LOAD_LHU:
            aluop_lhu =aluload;
            break; 
         default:
            dec_ilg =aluload;
            break;
       }

    switch(func3)
        {
        case STORE_SB:
            aluop_sb =alustore;
            break;
        case STORE_SH:
            aluop_sh =alustore;
            break;
         case STORE_SW:
            aluop_sw =alustore;
            break;
         default:
            dec_ilg =alustore;
            break;
       }

       //
       dec_raw_exe_rs1 =   (dec_rden_clked & (dec_rdidx_clked==rs1idx && rs1en));
       dec_raw_exe_rs2 =   (dec_rden_clked & (dec_rdidx_clked==rs2idx && rs2en));
                                      
       dec_raw_memwb_rs1 =     (exe_rden_clked & (exe_rdidx_clked==rs1idx && rs1en));   //memwb
       dec_raw_memwb_rs2 =     (exe_rden_clked & (exe_rdidx_clked==rs2idx && rs2en));   //memwb
                                      
       

       dec_stall = dec_raw_exe_rs1 | dec_raw_exe_rs2 ? !exe_res_valid :
                   dec_raw_memwb_rs1 | dec_raw_memwb_rs2 ? !memwb_valid :
                                     (rs1en & (!rs1en_ack))  |  (rs2en & (!rs2en_ack));

       real_rs1v = !rs1en ? 0 :
                    dec_raw_exe_rs1 ? exe_res :
                    dec_raw_memwb_rs1 ? memwb_wdata : rs1v;

       real_rs2v = !rs2en ? 0 :
                   dec_raw_exe_rs2 ? exe_res :
                   dec_raw_memwb_rs2 ? memwb_wdata : rs2v;

       dec_ras_push = (opcode==OPCODE_JAL  & (rdidx==1 || rdidx==5)) |
               (opcode==OPCODE_JALR & (rdidx==1 || rdidx==5) & (rs1idx!=1 && rs1idx!=5)) |
               (opcode==OPCODE_JALR & (rdidx==1 || rdidx==5) & (rs1idx==1 || rs1idx==5)) ;
    //dec_ras_pop =  (opcode==OPCODE_JALR & (rdidx!=1 && rdidx!=5) & (rs1idx==1 || rs1idx==5)) |
    //     (opcode==OPCODE_JALR & (rdidx==1 || rdidx==5) & (rs1idx==1 || rs1idx==5) & (rdidx!=rs1idx)) ;

    //   dec_branch_pdict_fail_pc =  decpc_clked + (!fet_predict_jmp_clked ? s_b_imm : 
    //                                              fet_ir16_clked ? 2 : 4);
    //   dec_jalr_tadr =  real_rs1v + s_i_imm;

    //control transfer instrution, need a 32bit ADDER
       cti_pc_op1 = alubranch ? decpc_clked : real_rs1v;
       cti_pc_op2 = alubranch ? (!fet_predict_jmp_clked ? s_b_imm :  fet_ir16_clked ? 2 : 4) : s_i_imm;
       cti_pc = cti_pc_op1 + cti_pc_op2;

    //current-inst is JALR at decode stage, JALR target address is fetpc_clked at fetch stage
       dec_jalr_pdict_fail = alujalr & (cti_pc!=fetpc_clked);

}
