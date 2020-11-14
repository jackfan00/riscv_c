#include "execu.h"
#include "decode.h"

void execu_clked()
{
 exe_res_clked        = exe_res;
 exe_res_valid_clked  = exe_res_valid;
 exe_rden_clked       = exe_rden;
 exe_rdidx_clked      = dec_rdidx_clked;

 //ras
 if (dec_ras_push_clked){
     ras_stack[ras_sp] = exe_res;
     ras_sp++;
 }

}
