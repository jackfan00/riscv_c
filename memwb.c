#include "memwb.h"
#include "execu.h"
#include "mul.h"
#include "memwb_bus.h"
#include "lif.h"

void memwb()
{
    BIT exeres2regw_stall;
    int i;
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
    //memwb_idx = o_memwb_bus_cmd_adr; //exe_rdidx_clked;
    o_memwb_bus_cmd_ready = memwb_ready;
    memwb_valid = o_memwb_bus_cmd_valid ;
    memwb_id = o_memwb_bus_cmd_id;
    //
    //memwb_stall = exe_rden_clked & (  (!memwb_ready) || 
    //                                   !(exe_aluload_clked ? lsu2mem_rsp_valid : exe_res_valid_clked ) ||
    //                                   !(exe_muldiv_clked ? mul_rsp_valid : exe_res_valid_clked ) 
    //                            );
    memwb_idx = lifvalid_clked[memwb_id*2] ? lifrdidx_clked[memwb_id*2] : exe_rdidx_clked;
    
    //normal exe result is low priority to write regs
    //if regw conflicts with other reqs(mul/div/lsu)
    //pipeline will be stalled
    //if (mul/div/lsu) conflicts with others, stall-controll code at execu stage
    exeres2regw_stall = i_memwb_bus_cmd_valid[EXEBUSID] & (!i_memwb_bus_cmd_ready[EXEBUSID]);

    memwb_stall = (memwb_valid & (!memwb_ready)) | exeres2regw_stall;
}
