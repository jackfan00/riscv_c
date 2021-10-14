#include "lowclkgen.h"

void lowclkgen()
{
    cloclkrem_carry = (lowclkrem_acc_clked>>16);
    clk32768_p = (clk32768_cnt_clked==(LOWCLKDIV-1+cloclkrem_carry));
    lowclkrem_acc = (lowclkrem_acc_clked & 0xffff) + LOWCLKREM;
    clk32768_cnt = clk32768_p ? 0 : clk32768_cnt_clked+1;

    us_p = (clkus_cnt_clked==(HCLKMHZ-1));
    clkus_cnt = us_p ? 0 : clkus_cnt_clked+1;

}