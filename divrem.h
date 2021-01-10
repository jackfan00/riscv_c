#ifndef DIVREM_H
#define DIVREM_H
void divrem();
void divrem_clked();

#include "reg.h"

//input 

REG32 divrem_opd1;
REG32 divrem_opd2;
BIT div0_clked;
BIT ovflow_clked;
REG32 quo_undivsigned_clked;
REG32 rem_undivsigned_clked;
BIT div_end_p_clked;
REG32 divisor_undivsigned_clked;
REG32 dividend_undivsigned_clked;
BIT divorrem_clked;
REG8 divremcnt_clked;
REG32 minued_clked;
BIT diven_clked;
REG32 q_clked;
BIT divisor_signed_clked;
BIT dividend_signed_clked;
REG32 dividend_clked;
  REG8 divregidx_clked;
  BIT divrden_clked;

//output
REG8 inik;
BIT diven_p;
BIT div_end_p;
REG32 nxtrem;
REG32 nxt_q;
REG32 iniminued;
REG32 divisor_undivsigned;
REG32 dividend_undivsigned;
BIT divsigned;
BIT div0;
BIT ovflow;
BIT divorrem;
BIT divisor_signed;
BIT dividend_signed;
REG32 dividend;
REG32 nxt_minued;
//
  BIT qbit;
  REG32 newminued;
  REG32 remsigned;
  REG32 quosigned;
  REG32 remres;
  REG32 quores;

  REG8 divregidx;
  BIT divrden;

#endif //DIVREM_H