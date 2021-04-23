#include "lowclkgen.h"

void lowclkgen_clked()
{
    cpuclk_cnt_clked = cpuclk_cnt;  
    lowclkrem_acc_clked = clk32768_p ? lowclkrem_acc : lowclkrem_acc_clked;
}