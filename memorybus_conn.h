#include "memorybus.h"
#include "fetch.h"

i_bus_cmd_valid[0]= ifu2mem_cmd_valid;
i_bus_cmd_read[0]= ifu2mem_cmd_read;
i_bus_cmd_adr[0]= ifu2mem_cmd_adr;
i_bus_cmd_rwbyte[0]= ifu2mem_cmd_rwbyte;
i_bus_rsp_ready[0]= ifu2mem_rsp_ready;
ifu2mem_cmd_ready= i_bus_cmd_ready[0];
ifu2mem_rsp_valid= i_bus_rsp_valid[0];
ifu2mem_rsp_rdata= i_bus_rsp_rdata[0];
//ifu2mem_rsp_err = i_bus_rsp_err[0];
