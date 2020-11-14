#include "execu.h"
#include "decode.h"

void execu_clked()
{
    int i;

 exe_res_clked        = exe_res;
 exe_res_valid_clked  = exe_res_valid;
 exe_rden_clked       = exe_rden;
 exe_rdidx_clked      = dec_rdidx_clked;

 //ras stack push
 //JAL/JALR can not back-to-back, must seprate 3 instruction apart, because of pipeline issue.
 if (dec_ras_push_clked){
     for (i=RASDEPTH-1;i<=1;i--){
         ras_stack[i] = ras_stack[i-1];
     }
     ras_stack[0] = exe_res;
 }

}
