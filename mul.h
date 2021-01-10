#ifndef MUL_H
#define MUL_H
void mul();
void mul_clked();

#include "reg.h"

//input 
BIT mul_enable_clked;
REG8 mul_cycles_clked;
BIT mul_low_clked;
BIT mul_rsp_ready;
BIT mul_fused_clked;
REG8 mulregidx_clked;
BIT mulrden_clked;

//output

BIT mul_enable;
REG32 mulres;
BIT mul_low;
BIT mul_fused;

REG8 mulregidx;
BIT mulrden;

//for simulation only
long long mul64, mul64_clked;

#endif //MUL_H