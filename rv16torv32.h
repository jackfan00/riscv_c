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

REG32 rv16     ;
REG32 rv32     ;
REG32 c0_instr ;
REG32 c1_instr ; 
REG32 c2_instr ;
#endif //RV16TORV32_H

