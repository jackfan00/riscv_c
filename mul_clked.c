#include "mul.h"
#include "execu.h"

void mul_clked()
{
    // need to modify to fit hardware implementation
    mul_enable_clked =
                        mul_enable ? 1 : 
                         mul_rsp_valid & mul_rsp_ready ? 0 : 
                        mul_enable_clked;
    mul_low_clked = mul_enable ? mul_low :  mul_low_clked;
    mul64_clked = mul_enable ? mul64 : mul64_clked;
    mul_cycles_clked = mul_enable ? 1 :
                       mul_enable_clked ? mul_cycles_clked+1 : 0;
    mul_fused_clked = mul_fused;
    mulregidx_clked = mulregidx;              
    mulrden_clked   = mulrden;              
                   
                   
}