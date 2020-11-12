#include "execu.h"
#include "decode.h"

void execu_clked()
{
 exe_res_clked        = exe_res;
 exe_res_valid_clked  = exe_res_valid;
 exe_rden_clked       = dec_rden_clked;
 exe_rdidx_clked      = dec_rdidx_clked;

}
