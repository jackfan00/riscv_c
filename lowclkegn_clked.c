#include "lowclkgen.h"

void lowclkgen_clked()
{
    clk32768_cnt_clked = clk32768_cnt;  
    clkus_cnt_clked = clkus_cnt;  
    lowclkrem_acc_clked = clk32768_p ? lowclkrem_acc : lowclkrem_acc_clked;
}