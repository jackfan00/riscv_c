
#include "codebus.h"
#include "fetch.h"


void codebus_connect(){

i_codebus_cmd_valid[0]= ifu2mem_cmd_valid;
i_codebus_cmd_read[0]= ifu2mem_cmd_read;
i_codebus_cmd_adr[0]= ifu2mem_cmd_adr;
i_codebus_cmd_rwbyte[0]= ifu2mem_cmd_rwbyte;
i_codebus_rsp_ready[0]= ifu2mem_rsp_ready;
ifu2mem_cmd_ready= i_codebus_cmd_ready[0];
ifu2mem_rsp_valid= i_codebus_rsp_valid[0];
ifu2mem_rsp_rdata= i_codebus_rsp_rdata[0];
//ifu2mem_rsp_err = i_codebus_rsp_err[0];
}
