#ifndef GPIO_H
#define GPIO_H
void gpio();
void gpio_clked();

#include "reg.h"
#include "peripheral.h"

#define GPIO_VALUE     (GPIOBASE+0x0 )
#define GPIO_INPUT_EN  (GPIOBASE+0x4 )
#define GPIO_OUTPUT_EN (GPIOBASE+0x8 )
#define GPIO_PORT      (GPIOBASE+0xc )
#define GPIO_RISE_IE   (GPIOBASE+0x18)
#define GPIO_RISE_IP   (GPIOBASE+0x1c)
#define GPIO_FALL_IE   (GPIOBASE+0x20)
#define GPIO_FALL_IP   (GPIOBASE+0x24)
#define GPIO_HIGH_IE   (GPIOBASE+0x28)
#define GPIO_HIGH_IP   (GPIOBASE+0x2c)
#define GPIO_LOW_IE    (GPIOBASE+0x30)
#define GPIO_LOW_IP    (GPIOBASE+0x34)
#define GPIO_IOF_EN    (GPIOBASE+0x38)
#define GPIO_IOF_SEL   (GPIOBASE+0x3c)
#define GPIO_OUT_XOR   (GPIOBASE+0x40)

REG32 wGPIOPINS;
REG32 GPIOPINS;
REG32 gpio_oval_muxout;
REG32 gpio_oe_muxout;
REG32 gpio_ie_muxout;
REG32 iof_en;
REG32 iof_en_clked;
REG32 iof_sel;
REG32 iof_sel_clked;
REG32 iof1_oval;
REG32 iof0_oval;
REG32 iof1_oe;
REG32 iof0_oe;
REG32 iof1_ie;
REG32 iof0_ie;
REG32 gpio_reg_oval;
REG32 gpio_reg_oe;
REG32 gpio_reg_ie;
REG32 gpio_reg_xor;
REG32 gpio_reg_oval_clked;
REG32 gpio_reg_oe_clked;
REG32 gpio_reg_ie_clked;
REG32 gpio_reg_xor_clked;
REG32 gpio_oval;
REG32 gpio_ival;
REG32 gpio_ival_sync1;
REG32 gpio_ival_sync1_clked;
REG32 gpio_ival_sync2;
REG32 gpio_ival_sync2_clked;
REG32 iof_ival;
REG32 iof_ival_clked;
REG32 high_ip_t;
REG32 high_ip;
REG32 high_ip_clked;
REG32 low_ip_t;
REG32 low_ip;
REG32 low_ip_clked;
REG32 rise_ip_t;
REG32 rise_ip;
REG32 rise_ip_clked;
REG32 fall_ip_t;
REG32 fall_ip;
REG32 fall_ip_clked;
REG32 gpio_high_ie;
REG32 gpio_high_ie_clked;
REG32 gpio_low_ie;
REG32 gpio_low_ie_clked;
REG32 gpio_rise_ie;
REG32 gpio_rise_ie_clked;
REG32 gpio_fall_ie;
REG32 gpio_fall_ie_clked;
REG32 gpio_intr;
REG32 gpio_intr_clked;

//
BIT gpio_regcs;
BIT gpio_regw;
REG32 gpio_regwdata;
REG32 gpio_regwadr;
REG32 gpio_regradr;
BIT gpio_cmd_valid;
BIT gpio_cmd_ready;
BIT gpio_cmd_read;
REG32 gpio_cmd_adr;
REG32 gpio_cmd_data;
BIT gpio_rsp_valid;
BIT gpio_rsp_ready;
BIT gpio_rsp_read;
REG32 gpio_rsp_rdata;
BIT gpio_read;
REG32 gpio_rdat;
BIT gpio_write;
BIT gpio_read1st;
REG32 read_gpio_rdat;
BIT gpio_read_clked;
BIT gpio_write_clked;
BIT gpio_read1st_clked;
REG32 read_gpio_rdat_clked;
REG32 gpio_csadr_clked;
#endif //GPIO_H