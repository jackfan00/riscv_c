#include "memwb.h"
#include "execu.h"

void memwb()
{
    if (lsu2mem_rsp_valid & exe_aluload_clked){
        memwb_wdata = lsu2mem_rsp_rdata;
        memwb_wdata = exe_lhu_clked ? (memwb_wdata& 0x0ffff) :
                      exe_lh_clked ? (memwb_wdata& 0x0ffff)+ 0xffff0000 :
                      exe_lbu_clked ? (memwb_wdata& 0x0ff) :
                      exe_lb_clked ? (memwb_wdata& 0x0ff)+ 0xffffff00 :
                      memwb_wdata;
    }
    else{
        memwb_wdata = exe_res_clked;
    }

    memwb_idx = exe_rdidx_clked;

    lsu2mem_rsp_ready = memwb_ready;
    memwb_valid = exe_rden_clked & (exe_res_valid_clked | lsu2mem_rsp_valid);

    //should not happen, because it has 1st priority for regwbus
    memwb_stall = memwb_valid & (!memwb_ready);

}
