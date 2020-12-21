#ifndef PERIPHERAL_H
#define PERIPHERAL_H
void peripheral();
void peripheral_clked();

#include "reg.h"

#define TXUARTADDR 0x10013000

//input
REG32 device_reg_clked;
BIT peripheral_read_clked;
REG32 peripheral_regradr_clked;
BIT peripheral_write_clked;
BIT peripheral_read1st_clked;
REG32 read_peripheral_rdat_clked;
REG32 peripheral_csadr_clked;

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
BIT peripheral_write;
BIT peripheral_read1st;
REG32 read_peripheral_rdat;
REG32 peripheral_rdat;

//uart
BIT txuart_wr;
REG8 txuart_char;
#endif //PERIPHERAL_H