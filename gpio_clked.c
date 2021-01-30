#include <stdio.h>

#include "gpio.h"
#include "simhw/simuart.h"

void gpio_clked()
{
    gpio_ival_sync1_clked = gpio_ival_sync1;
    gpio_ival_sync2_clked = gpio_ival_sync2;
    gpio_csadr_clked = gpio_regcs ? gpio_regwadr : gpio_csadr_clked;
    gpio_reg_oval_clked = gpio_reg_oval;
    gpio_reg_xor_clked = gpio_reg_xor;
    gpio_reg_oe_clked = gpio_reg_oe;
    gpio_reg_ie_clked = gpio_reg_ie;
    iof_en_clked = iof_en;
    iof_sel_clked = iof_sel;
    gpio_high_ie_clked = gpio_high_ie;
    gpio_low_ie_clked = gpio_low_ie;
    gpio_rise_ie_clked = gpio_rise_ie;
    gpio_fall_ie_clked = gpio_fall_ie;
    high_ip_clked = high_ip;
    low_ip_clked  = low_ip;
    rise_ip_clked = rise_ip;
    fall_ip_clked = fall_ip;
    iof_ival_clked = iof_ival;
    gpio_intr_clked = gpio_intr;

    //
    gpio_read_clked = gpio_read;
    gpio_write_clked = gpio_write;
    gpio_read1st_clked = gpio_read1st;
    read_gpio_rdat_clked = read_gpio_rdat;

    //
    *gpio_shmptr = GPIOPINS;
    wGPIOPINS = *(gpio_shmptr+1);

    if (gpio_write){
        printf("gpio_adr:0x%x, gpio_wdat:0x%x\n",gpio_regwadr, gpio_regwdata);
    //    exit(9);
    }

}