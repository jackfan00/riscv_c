#ifndef MUL_H
#define MUL_H
#include "reg.h"

//input 
BIT mul_enable_clked;
REG8 mul_cycles_clked;
BIT mul_low_clked;
BIT mul_rsp_ready;

//output
BIT mul_cmd_ready;
BIT mul_rsp_valid;
BIT mul_enable;
REG32 mulres;
BIT mul_low;


//for simulation only
long long mul64, mul64_clked;

#endif //MUL_H