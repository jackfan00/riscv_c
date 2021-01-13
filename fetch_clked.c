#include "fetch.h"
#include "execu.h"
#include "decode.h"
#include "memwb.h"
#include "csrreg.h"
#include "opcode_define.h"

void fetch_clked()
{
    int i;

    // 

    if ((!exe_stall) && (!dec_stall) && (!memwb_stall) && (!csr_exception_stall)){

 decpc_clked = fetpc_clked;
 dec_ir16_clked = fet_ir16;

    memIR_hi16_clked = memIR_hi16;
    fetpc_clked = pc;
    fet_ir16_clked =  fet_ir16;
    remain_ir16s_clked = remain_ir16s;
    pc_keep_clked = pc_keep;

    //fetpc_clked corresponding to fetchIR, not fetchIR_clked

    ifu_cmd_adr_clked = ifu_cmd_valid & ifu_cmd_ready ? ifu_cmd_adr : ifu_cmd_adr_clked;

    //use for mtval
    fetchIR16_clked = fet_ir16 ? memIR16 : fetchIR16_clked;

    fetchIR_clked = dec_flush ? NOP : fetchIR;
    //fet_ir16_clked = dec_flush ? 0 : fet_ir16;
    fet_predict_jmp_clked = fet_predict_jmp;
    //branchjmp_hipart_clked = branchjmp_hipart;

    //
    if (new_midnxtpc_part2_fg)
        new_midnxtpc_part2_fg_clked = 1;
    else if (ifu_cmd_valid & ifu_cmd_ready)
        new_midnxtpc_part2_fg_clked = 0;

    // ras stack pop
    if (fet_ras_pop){
      for (i=0;i<(RASDEPTH-1);i++){
         ras_stack[i] = ras_stack[i+1];
       }
    }

    // control read new instruction
    //ensure at first cycle ,remain_ir16s_clked number is correct
    //remain_ir16s_clked = 
    //                        remain_ir16s;

    firstinst_clked = ifu_cmd_valid & ifu_cmd_ready ? 0 : firstinst_clked;

    }

buffered_rsp_rdata_clked = buffered_rsp_rdata;

ifu_rsp_valid_clked = ifu_rsp_valid & fetch_stall ? 1 :
                          !fetch_stall ? 0 :  ifu_rsp_valid_clked ;

fetch_stall_clked = fetch_stall;

}
