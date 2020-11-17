#include "memwb.h"
#include "execu.h"
#include "mul.h"
#include "memwb_bus.h"

void memwb()
{
    //write-back arbitor
    /*
    if (lsu2mem_rsp_valid & exe_aluload_clked){
        memwb_wdata = lsu2mem_rsp_rdata;
        memwb_wdata = exe_lhu_clked ? (memwb_wdata& 0x0ffff) :
                      exe_lh_clked ? (memwb_wdata& 0x0ffff)+ (memwb_wdata&0x8000 ? 0xffff0000 : 0) :
                      exe_lbu_clked ? (memwb_wdata& 0x0ff) :
                      exe_lb_clked ? (memwb_wdata& 0x0ff)+ (memwb_wdata&0x80 ? 0xffffff00 : 0) :
                      memwb_wdata;
    }
    else if ((MUL_RSPVALID_CYCLES>0) & exe_muldiv_clked & mul_rsp_valid){
        memwb_wdata = mulres;
    }
    else{
        memwb_wdata = exe_res_clked;
    }*/



    //
    memwb_wdata = o_memwb_bus_cmd_wdata;
    memwb_idx = o_memwb_bus_cmd_adr; //exe_rdidx_clked;
    o_memwb_bus_cmd_ready = memwb_ready;
    memwb_valid = exe_rden_clked & o_memwb_bus_cmd_valid ;

    //
    //memwb_stall = exe_rden_clked & (  (!memwb_ready) || 
    //                                   !(exe_aluload_clked ? lsu2mem_rsp_valid : exe_res_valid_clked ) ||
    //                                   !(exe_muldiv_clked ? mul_rsp_valid : exe_res_valid_clked ) 
    //                            );

    memwb_stall = memwb_valid & (!memwb_ready);
}
