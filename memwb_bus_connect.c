#include "memwb_bus.h"
#include "memwb.h"
#include "execu.h"

void memwb_bus_connect(){

i_memwb_bus_cmd_valid[0]= div_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
i_memwb_bus_cmd_adr[0]= div_rsp_adr;
i_memwb_bus_cmd_wdata[0]= div_rsp_rdata;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
div_rsp_ready= i_memwb_bus_cmd_ready[0];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[1]= lsu2mem_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
i_memwb_bus_cmd_adr[1]= lsu2mem_rsp_adr;
i_memwb_bus_cmd_wdata[1]= lsu2mem_rsp_rdata;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
lsu2mem_rsp_ready= i_memwb_bus_cmd_ready[1];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[2]= mul_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
i_memwb_bus_cmd_adr[2]= mul_rsp_adr;
i_memwb_bus_cmd_wdata[2]= mul_rsp_rdata;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
mul_rsp_ready= i_memwb_bus_cmd_ready[2];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[3]= exe_res_valid_clked;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
i_memwb_bus_cmd_adr[3]= exe_rdidx_clked;
i_memwb_bus_cmd_wdata[3]= exe_res_clked;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
//exe_res_clked_rsp_ready= i_memwb_bus_cmd_ready[3];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

}
