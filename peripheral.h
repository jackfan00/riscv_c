#ifndef PERIPHERAL_H
#define PERIPHERAL_H
void peripheral();
void peripheral_clked();

#include "reg.h"
#include "pwm.h"

#define GPIOBASE 0x10012000
#define UART0BASE 0x10013000

#define UART0_TXDATA_ADR 0x10013000
#define UART0_RXDATA_ADR 0x10013004
#define UART0(x) ((x&0xfffff000)==UART0BASE)
#define UART0_TXDATA(x) (x==UART0_TXDATA_ADR)
#define GPIO(x) ((x&0xfffff000)==GPIOBASE)
#define PWM2(x) ((x&0xfffff000)==PWM2_BASE)
#define CTRADIO(x) ((x&0xfffff000)==CT_RADIO_BASE)

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
BIT txuart0_wr;
REG8 txuart0_char;
#endif //PERIPHERAL_H