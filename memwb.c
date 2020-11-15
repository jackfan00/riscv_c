#include "memwb.h"
#include "execu.h"

void memwb()
{
    if (lsu2mem_rsp_valid & exe_aluload_clked){
        memwb_wdata = lsu2mem_rsp_rdata;
        memwb_wdata = exe_lhu_clked ? (memwb_wdata& 0x0ffff) :
                      exe_lh_clked ? (memwb_wdata& 0x0ffff)+ (memwb_wdata&0x8000 ? 0xffff0000 : 0) :
                      exe_lbu_clked ? (memwb_wdata& 0x0ff) :
                      exe_lb_clked ? (memwb_wdata& 0x0ff)+ (memwb_wdata&0x80 ? 0xffffff00 : 0) :
                      memwb_wdata;
    }
    else{
        memwb_wdata = exe_res_clked;
    }

    memwb_idx = exe_rdidx_clked;

    lsu2mem_rsp_ready = memwb_ready;
    memwb_valid = exe_rden_clked & (exe_aluload_clked ? lsu2mem_rsp_valid : exe_res_valid_clked );

    //
    memwb_stall = exe_rden_clked & (  (!memwb_ready) || 
                                       !(exe_aluload_clked ? lsu2mem_rsp_valid : exe_res_valid_clked )
                                );

}
