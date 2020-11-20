#include "memwb_bus.h"
#include "memwb.h"
#include "execu.h"
#include "mul.h"

void memwb_bus_connect(){

i_memwb_bus_cmd_valid[DIVBUSID]= div_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
//i_memwb_bus_cmd_adr[DIVBUSID]= div_rsp_adr;
i_memwb_bus_cmd_wdata[DIVBUSID]= div_rsp_rdata;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
div_rsp_ready= i_memwb_bus_cmd_ready[DIVBUSID];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[LSUBUSID]= lsu2mem_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
//i_memwb_bus_cmd_adr[LSUBUSID]= lsu2mem_rsp_adr;
i_memwb_bus_cmd_wdata[LSUBUSID]= lsu2mem_rsp_rdata;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
lsu2mem_rsp_ready= i_memwb_bus_cmd_ready[LSUBUSID];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[MULBUSID]= mul_rsp_valid;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
//i_memwb_bus_cmd_adr[MULBUSID]= mul_rsp_adr;
i_memwb_bus_cmd_wdata[MULBUSID]= mulres;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
mul_rsp_ready= i_memwb_bus_cmd_ready[MULBUSID];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

//
i_memwb_bus_cmd_valid[EXEBUSID]= exe_rden_clked & exe_res_valid_clked;
//i_memwb_bus_cmd_read[0]= div_cmd_read;
//i_memwb_bus_cmd_adr[EXEBUSID]= exe_rdidx_clked;
i_memwb_bus_cmd_wdata[EXEBUSID]= exe_res_clked;
//i_memwb_bus_cmd_rwbyte[0]= div_cmd_rwbyte;
//i_memwb_bus_rsp_ready[0]= div_rsp_ready;
//exe_res_clked_rsp_ready= i_memwb_bus_cmd_ready[EXEBUSID];
//div_rsp_valid= i_memwb_bus_rsp_valid[0];
//div_rsp_rdata= i_memwb_bus_rsp_rdata[0];
//div_rsp_err = i_memwb_bus_rsp_err[0];

}
