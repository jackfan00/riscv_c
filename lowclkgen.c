#include "lowclkgen.h"

void lowclkegn()
{
    cloclkrem_carry = (lowclkrem_acc_clked>>16);
    clk32768_p = (cpuclk_cnt_clked==(LOWCLKDIV+cloclkrem_carry));
    lowclkrem_acc = (lowclkrem_acc_clked & 0xffff) + LOWCLKREM;
    cpuclk_cnt = clk32768_p ? 0 : cpuclk_cnt_clked+1;

}