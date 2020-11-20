#include "fetch.h"
#include "execu.h"
#include "decode.h"
#include "memwb.h"

void fetch_clked()
{
    int i;

    if ((!exe_stall) && (!dec_stall) && (!memwb_stall)){

    firstinst_clked = ifu2mem_cmd_valid & ifu2mem_cmd_ready ? 0 : firstinst_clked;
    //fetpc_clked corresponding to fetchIR, not fetchIR_clked
    fetpc_clked = pc;
    fetchIR_clked = fetchIR;
    memIR_hi16_clked = memIR_hi16;
    fet_predict_jmp_clked = fet_predict_jmp;
    fet_ir16_clked = fet_ir16;
    //branchjmp_hipart_clked = branchjmp_hipart;

    //
    if (new_midnxtpc_part2_fg)
        new_midnxtpc_part2_fg_clked = 1;
    else if (ifu2mem_cmd_valid & ifu2mem_cmd_ready)
        new_midnxtpc_part2_fg_clked = 0;

    // ras stack pop
    if (fet_ras_pop){
      for (i=0;i<(RASDEPTH-1);i++){
         ras_stack[i] = ras_stack[i+1];
       }
    }

    }
}
