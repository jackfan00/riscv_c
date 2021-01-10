#include <stdio.h>
#include "uart.h"
#include "simhw/simuart.h"


void uart_clked()
{
    // communcate with fakerxuart via IPC share memory
    //check uart rxbuffer
    if (rxuart_done){
            //uart_rxdata_clked = (*rxuart0_shmptr) | (1<<31);
            *rxuart0_shmptr=(1<<31);
    }

    uart_read_clked = uart_read;
    uart_write_clked = uart_write;
    uart_read1st_clked = uart_read1st;
    read_uart_rdat_clked = read_uart_rdat;
    uart_csadr_clked = uart_regcs ? uart_regwadr : uart_csadr_clked;



    // communcate with fakerxuart via IPC share memory
    if (uart_wr_txdata){
        *txuart0_shmptr = uart_txdata;
    }
    uart_txdata_clked = *txuart0_shmptr;

    

}