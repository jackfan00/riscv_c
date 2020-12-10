#ifndef PERIPHERAL_H
#define PERIPHERAL_H
void peripheral();
void peripheral_clked();

#include "reg.h"


//input
REG32 device_reg_clked;
BIT peripheral_read_clked;
REG32 peripheral_regradr_clked;

//output
BIT peripheral_regcs;
BIT peripheral_regwr;
REG32 peripheral_regwdata;
REG32 peripheral_regwadr;
REG32 peripheral_regradr;
BIT peripheral_cmd_valid;
BIT peripheral_cmd_ready;
BIT peripheral_cmd_read;
REG32 peripheral_cmd_adr;
REG32 peripheral_cmd_data;
BIT peripheral_rsp_valid;
BIT peripheral_rsp_ready;
BIT peripheral_rsp_read;
REG32 peripheral_rsp_rdata;
REG32 device_reg;
BIT peripheral_read;

#endif //PERIPHERAL_H