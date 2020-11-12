
#include "regbus.h"
#include "execu.h"
#include "memwb.h"


void regwbus_connect(){

i_regwbus_cmd_valid[0]= memwb_valid;
//i_regwbus_cmd_read[0]= 1;
i_regwbus_cmd_adr[0]  = memwb_idx;
i_regwbus_cmd_wdata[0]=memwb_wdata;
//i_regwbus_cmd_rwbyte[0]= 0xf;
//i_regwbus_rsp_ready[0]= 1;
memwb_ready= i_regwbus_cmd_ready[0];
//rs1v = i_regwbus_rsp_rdata[0];
//ifu2mem_rsp_err = i_regwbus_rsp_err[0];

}
