#ifndef LOWCLKGEN_H
#define LOWCLKGEN_H
void lowclkgen();
void lowclkgen_clked();

#include "reg.h"

#define HCLKMHZ    16
#define CPUCLKFREQ (HCLKMHZ*1000000)
#define LOWCLKFREQ 32768
#define LOWCLKDIV (CPUCLKFREQ/LOWCLKFREQ)
#define LOWCLKREM (CPUCLKFREQ%LOWCLKFREQ)

BIT cloclkrem_carry;
BIT clk32768_p;
REG32 lowclkrem_acc;
REG32 lowclkrem_acc_clked;
REG32 cpuclk_cnt_clked;
REG32 cpuclk_cnt;

#endif //LOWCLKGEN_H