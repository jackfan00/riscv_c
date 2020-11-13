
#include "regbus.h"
#include "decode.h"
#include "fetch.h"


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


i_rs1bus_cmd_valid[1]= fet_rs1en;
//i_rs1bus_cmd_read[0]= 1;
i_rs1bus_cmd_adr[1]= fet_rs1idx;
//i_rs1bus_cmd_rwbyte[0]= 0xf;
i_rs1bus_rsp_ready[1]= 1;
//rs1en_ack = i_rs1bus_cmd_ready[0];
fet_rs1en_ack= i_rs1bus_rsp_valid[1];
fet_rs1v = i_rs1bus_rsp_rdata[1];
//ifu2mem_rsp_err = i_rs1bus_rsp_err[0];

}
