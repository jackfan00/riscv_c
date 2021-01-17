#include "gpio.h"
#include "uart.h"

void gpio()
{
    int i;
    REG32 gpio_oval_muxout_tmp;
    REG32 gpio_oe_muxout_tmp;
    REG32 gpio_ie_muxout_tmp;


    //
    gpio_oval_muxout=0;
    gpio_oe_muxout=0;
    gpio_ie_muxout=0;
    gpio_oval=0;
    gpio_ival=0;
    gpio_ival_sync1=0;
    gpio_ival_sync2=0;
    iof_ival=0;
    high_ip_t=0;
    low_ip_t=0;
    rise_ip_t=0;
    fall_ip_t=0;
    gpio_intr=0;

    //IOF mapping
    iof0_oe=0;
    iof0_oval=0;
    GPIOPINS=0xffffffff;
    iof0_oval |= (txuartPIN<<17); 
    iof0_oe |= (1<<17);
    GPIOPINS &= ((rxuartPIN<<16) | (~(1<<16)));   //simulate rxuart pin toggle

    //
    for (i=0;i<32;i++){
        gpio_oval_muxout_tmp = iof_en_clked&(1<<i) ? 
                            (iof_sel_clked&(1<<i) ? iof1_oval&(1<<i) : iof0_oval&(1<<i)) : 
                                gpio_reg_oval_clked&(1<<i);
        gpio_oval_muxout |= gpio_oval_muxout_tmp;  

        gpio_oe_muxout_tmp = iof_en_clked&(1<<i) ? 
                            (iof_sel_clked&(1<<i) ? iof1_oe&(1<<i) : iof0_oe&(1<<i)) : 
                                gpio_reg_oe_clked&(1<<i);
        gpio_oe_muxout |= gpio_oe_muxout_tmp;             

        gpio_ie_muxout_tmp = iof_en_clked&(1<<i) ? 
                            (iof_sel_clked&(1<<i) ? iof1_ie&(1<<i) : iof0_ie&(1<<i)) : 
                                gpio_reg_ie_clked&(1<<i);
        gpio_ie_muxout |= gpio_ie_muxout_tmp;

        gpio_oval |= (gpio_reg_xor_clked&(1<<i)) ^ (gpio_oval_muxout&(1<<i));
        GPIOPINS &= gpio_oe_muxout&(1<<i) ? gpio_oval|(~(1<<i)) : GPIOPINS; //(1<<i); //1 mean pull-up
        gpio_ival |= gpio_ie_muxout&(1<<i) ? GPIOPINS&(1<<i)  : 0;
        gpio_ival_sync1 |= gpio_ival&(1<<i);
        gpio_ival_sync2 |= gpio_ival_sync1_clked&(1<<i);
        iof_ival |= gpio_ival_sync2_clked&(1<<i);
        //interrupt
        high_ip_t |= //gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_HIGH_IP) & (gpio_regwdata&(1<<i)) ? 0:
                        high_ip_clked&(1<<i) | iof_ival_clked&(1<<i);
        low_ip_t |= //gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_LOW_IP) & (gpio_regwdata&(1<<i)) ? 0:
                        low_ip_clked&(1<<i) | (!iof_ival_clked&(1<<i));
        rise_ip_t |= //gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_RISE_IP) & (gpio_regwdata&(1<<i)) ? 0:
                        rise_ip_clked&(1<<i) | ((!iof_ival_clked&(1<<i)) & iof_ival&(1<<i));
        fall_ip_t |= //gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_FALL_IP) & (gpio_regwdata&(1<<i)) ? 0:
                        fall_ip_clked&(1<<i) | (iof_ival_clked&(1<<i) & (!iof_ival&(1<<i)));
        gpio_intr |=  (gpio_high_ie_clked&(1<<i)&high_ip_clked&(1<<i)) |
                        (gpio_low_ie_clked&(1<<i) &low_ip_clked&(1<<i) ) |
                        (gpio_rise_ie_clked&(1<<i)&rise_ip_clked&(1<<i)) |
                        (gpio_fall_ie_clked&(1<<i)&fall_ip_clked&(1<<i)) ;
    }
    //
    gpio_cmd_ready = (!gpio_rsp_valid) | (gpio_rsp_valid&gpio_rsp_ready);
    gpio_regcs = gpio_cmd_valid & gpio_cmd_ready;
    gpio_regw = !gpio_cmd_read;
    gpio_regwadr = gpio_cmd_adr;
    gpio_regwdata = gpio_cmd_data;
    gpio_read =    gpio_regcs & (!gpio_regw) ? 1 : 
                    gpio_read_clked&gpio_rsp_ready ? 0 :
                    gpio_read_clked;
    gpio_write = gpio_regcs  & (gpio_regw) ? 1: 
                       gpio_write_clked& gpio_rsp_ready ? 0 :
                       gpio_write_clked;
    gpio_rsp_valid = gpio_read_clked | gpio_write_clked ? 1 : 0;
    gpio_read1st = gpio_regcs & (!gpio_regw) ? 1: 0;
    read_gpio_rdat = gpio_read1st_clked ? gpio_rdat : read_gpio_rdat_clked;
    gpio_rsp_rdata =  (gpio_read1st_clked ? gpio_rdat : read_gpio_rdat_clked)  ;
    gpio_rsp_read =  gpio_read_clked;    

    //reg write
    gpio_reg_oval = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_PORT) ? gpio_regwdata : gpio_reg_oval_clked;
    gpio_reg_xor = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_OUT_XOR) ? gpio_regwdata : gpio_reg_xor_clked;
    gpio_reg_oe = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_OUTPUT_EN) ? gpio_regwdata : gpio_reg_oe_clked;
    gpio_reg_ie = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_INPUT_EN) ? gpio_regwdata : gpio_reg_ie_clked;
    iof_en = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_IOF_EN) ? gpio_regwdata : iof_en_clked;
    iof_sel = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_IOF_SEL) ? gpio_regwdata : iof_sel_clked;
    gpio_high_ie = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_HIGH_IE) ? gpio_regwdata : gpio_high_ie_clked;
    gpio_low_ie = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_LOW_IE) ? gpio_regwdata : gpio_low_ie_clked;
    gpio_rise_ie = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_RISE_IE) ? gpio_regwdata : gpio_rise_ie_clked;
    gpio_fall_ie = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_FALL_IE) ? gpio_regwdata : gpio_fall_ie_clked;
    high_ip = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_HIGH_IP) ? gpio_regwdata : high_ip_t;
    low_ip = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_LOW_IP) ? gpio_regwdata : low_ip_t;
    rise_ip = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_RISE_IP) ? gpio_regwdata : rise_ip_t;
    fall_ip = gpio_regcs & gpio_regw & (gpio_regwadr==GPIO_FALL_IP) ? gpio_regwdata : fall_ip_t;


    //regrdata
    gpio_rdat = 
                (gpio_csadr_clked==GPIO_PORT) ? gpio_reg_oval_clked :
                (gpio_csadr_clked==GPIO_OUT_XOR) ? gpio_reg_xor_clked :
                (gpio_csadr_clked==GPIO_OUTPUT_EN) ? gpio_reg_oe_clked :
                (gpio_csadr_clked==GPIO_INPUT_EN) ? gpio_reg_ie_clked :
                (gpio_csadr_clked==GPIO_IOF_EN) ? iof_en_clked :
                (gpio_csadr_clked==GPIO_IOF_SEL) ? iof_sel_clked :
                (gpio_csadr_clked==GPIO_HIGH_IE) ? gpio_high_ie_clked :
                (gpio_csadr_clked==GPIO_LOW_IE) ? gpio_low_ie_clked :
                (gpio_csadr_clked==GPIO_RISE_IE) ? gpio_rise_ie_clked :
                (gpio_csadr_clked==GPIO_FALL_IE) ? gpio_fall_ie_clked :
                (gpio_csadr_clked==GPIO_HIGH_IP) ? high_ip_clked :
                (gpio_csadr_clked==GPIO_LOW_IP) ? low_ip_clked :
                (gpio_csadr_clked==GPIO_RISE_IP) ? rise_ip_clked :
                (gpio_csadr_clked==GPIO_FALL_IP) ? fall_ip_clked :
                (gpio_csadr_clked==GPIO_VALUE) ? iof_ival_clked :
                 0;

}