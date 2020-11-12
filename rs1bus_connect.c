
#include "regbus.h"
#include "decode.h"


void rs1bus_connect(){

i_rs1bus_cmd_valid[0]= rs1en;
//i_rs1bus_cmd_read[0]= 1;
i_rs1bus_cmd_adr[0]= rs1idx;
//i_rs1bus_cmd_rwbyte[0]= 0xf;
i_rs1bus_rsp_ready[0]= 1;
//rs1en_ack = i_rs1bus_cmd_ready[0];
rs1en_ack= i_rs1bus_rsp_valid[0];
rs1v = i_rs1bus_rsp_rdata[0];
//ifu2mem_rsp_err = i_rs1bus_rsp_err[0];

}
