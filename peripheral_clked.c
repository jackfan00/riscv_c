#include <stdio.h>
#include "peripheral.h"
#include "fetch.h"

void peripheral_clked()
{
    peripheral_read_clked = peripheral_read;
    peripheral_write_clked = peripheral_write;
    peripheral_read1st_clked = peripheral_read1st;
    read_peripheral_rdat_clked = read_peripheral_rdat;
    peripheral_csadr_clked = peripheral_regcs ? peripheral_regwadr : peripheral_csadr_clked;

    device_reg_clked = device_reg;
    //
    if (txuart0_wr){
        printf("%c",txuart0_char); 
        //printf("--pc=%08x,--%d\n",fetpc_clked, clockcnt); 
        //exit(2);
        //*shm_txuart = (char) txuart_char;
    }



}