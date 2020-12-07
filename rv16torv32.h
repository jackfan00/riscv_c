#ifndef RV16TORV32_H
#define RV16TORV32_H

#include "reg.h"

BIT CADDI4SPN ;
BIT CLW       ;
BIT CSW       ;
BIT CNOP      ;
BIT CADDI     ;
BIT CJAL      ;
BIT CLI       ;
BIT CADDI16SP ;
BIT CLUI      ;
BIT CSRLI     ;
BIT CSRAI     ;
BIT CANDI     ;
BIT CSUB      ;
BIT CXOR      ;
BIT COR       ;
BIT CAND      ;
BIT CJ        ;
BIT CBEQZ     ;
BIT CBNEZ     ;
BIT CSLLI     ;
BIT CLWSP     ;
BIT CJR       ;
BIT CMV       ;
BIT CBREAK    ;
BIT CJALR     ;
BIT CADD      ;
BIT CSWSP     ;

    REG32 c0_rdprime;
    REG32 c0_rs2prime;
    REG32 c0_rs1prime;
    REG32 c0_uimm;
    REG32 c0_uimm62;
    REG32 c0_nzuimm;

    REG32 c1_rs2prime;
    REG32 c1_rs1prime;
    REG32 c1_rdprime;
    REG32 c1_rs1;
    REG32 c1_rd;
    REG32 c1_nzimm;
    REG32 c1_jalimm;
    REG32 c1_jalimm111;
    REG32 c1_imm;
    REG32 c1_addi16sp_nzimm;
    REG32 c1_addi16sp_nzimm94;
    REG32 c1_lui_nzuimm;
    REG32 c1_shamt;
    REG32 c1_bxx_offset;
    REG32 c1_bxx_offset81;

    REG32 hlp10;
    REG32 hlp65;
    REG32 hlp1110;
    REG32 hlp1210;
    REG32 hlp1513;

    REG32 c2_shamt;
    REG32 c2_lw_offset;
    REG32 c2_lw_offset72;
    REG32 c2_rs1;
    REG32 c2_rd;
    REG32 c2_rs2;
    REG32 c2_sw_offset;
    REG32 c2_sw_offset72;

REG16 rv16     ;
REG32 rv32     ;
REG32 c0_instr ;
REG32 c1_instr ; 
REG32 c2_instr ;
#endif //RV16TORV32_H

