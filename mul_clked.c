#include "mul.h"

void mul_clked()
{
    // need to modify to fit hardware implementation
    mul_enable_clked = mul_rsp_valid ? 0 : 
                        mul_enable ? 1 : mul_enable_clked;
    mul_low_clked = mul_enable ? mul_low :  mul_low_clked;
    mul64_clked = mul_enable ? mul64 : mul64_clked;
    mul_cycles_clked = mul_enable ? 1 :
                       mul_enable_clked ? mul_cycles_clked+1 : 0;
}