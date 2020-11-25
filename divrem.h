#ifndef DIVREM_H
#define DIVREM_H

#include "reg.h"

//input 
BIT divrem_cmd_valid;
BIT divrem_cmd_ready;
REG32 divrem_opd1;
REG32 divrem_opd2;

//output
REG8 inik;
BIT diven_p;
BIT div_end_p;
REG8 divremcnt_clked;
BIT diven_clked;
REG32 minued_clked;
REG32 q_clked;
REG32 nxtrem;
REG32 nxt_q;
REG32 iniminued;
REG32 quo_clked;
REG32 rem_clked;
REG32 divisor;
REG32 dividend;
BIT div0;
BIT divsigned;
BIT ovflow;
BIT div_end_p_clked;
BIT div_rsp_valid;
BIT div_rsp_ready;
REG32 div_rsp_rdata;
BIT divorrem;
BIT divorrem_clked;
REG32 divisor_clked;
REG32 dividend_clked;


#endif //DIVREM_H