#include <stdio.h>
#include "peripheral.h"

void peripheral_clked()
{
    peripheral_read_clked = peripheral_read;
    peripheral_write_clked = peripheral_write;
    peripheral_read1st_clked = peripheral_read1st;
    read_peripheral_rdat_clked = read_peripheral_rdat;
    peripheral_csadr_clked = peripheral_regcs ? peripheral_regwadr : peripheral_csadr_clked;

    device_reg_clked = device_reg;
    //
    if (txuart_wr){
        printf("%c",txuart_char);
    }

}