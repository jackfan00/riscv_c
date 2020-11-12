#include "memwb.h"
#include "execu.h"

void memwb()
{
    if (lsu2mem_rsp_valid){
        memwb_wdata = lsu2mem_rsp_rdata;
    }
    else{
        memwb_wdata = exe_res_clked;
    }

    memwb_idx = exe_rdidx_clked;

    lsu2mem_rsp_ready = memwb_ready;
    memwb_valid = exe_rden_clked & (exe_res_valid_clked | lsu2mem_rsp_valid);

    memwb_stall = memwb_valid & (!memwb_ready);

}
