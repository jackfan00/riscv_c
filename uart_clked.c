#include <stdio.h>
#include "uart.h"
#include "simhw/simuart.h"

#define SIM_UART_BIT_PER 8
#define SIM_UART_TX_PER 8<<8

void uart_clked()
{
    uart_read_clked = uart_read;
    uart_write_clked = uart_write;
    uart_read1st_clked = uart_read1st;
    read_uart_rdat_clked = read_uart_rdat;
    uart_csadr_clked = uart_regcs ? uart_regwadr : uart_csadr_clked;

    // all below code are simulate uart TX/RX hardware behavoir
    // need to impelment real hardware code
    //
    // communcate with fakerxuart via IPC share memory
    //simulate uart rx
    uart_rxdata_tmp = *rxuart0_shmptr;
    uartrx_per_end_p = (uartrx_per_cnt_clked==SIM_UART_TX_PER);
    if (uartrx_per_end_p){  //simulate rx uart done
        *rxuart0_shmptr=(1<<31);
        uartrx_per_clked =0;
        uartrx_per_cnt_clked =0;
    }
    else if ((uart_rxdata_tmp&0x80000000)==0){  //rxuart receive data
        uartrx_per_cnt_clked++;
        uartrx_per_clked =1;
    }
    else{
        uartrx_per_clked =0;
        uartrx_per_cnt_clked =0;
    }
    //simulate pin toggle
    rxuartPIN = uartrx_per_clked ? (uart_rxdata_tmp >> (uartrx_per_cnt_clked>>SIM_UART_BIT_PER)) & 0x01 : 1;
    //if (uartrx_per_clked){
    //    printf("%x-%d:%d\n",uart_rxdata_tmp,uartrx_per_cnt_clked,rxuartPIN);
    //}    

    //check uart rxbuffer
    if (uartrx_per_end_p){  //simulate rx uart done
        uart_rxdata_clked = uart_rxdata_tmp;
    }
    else if (rxuart_done){
            uart_rxdata_clked=(1<<31);
    }


    //
    //simulate uart tx 
    uarttx_per_end_p = (uarttx_per_cnt_clked==SIM_UART_TX_PER);
    uarttx_per_cnt_clked = uart_wr_txdata ? 0:
                            uarttx_per_clked ? uarttx_per_cnt_clked+1 :
                            0;
    if (uart_wr_txdata){
        uarttx_per_clked = 1;
    }
    else if (uarttx_per_end_p){
        uarttx_per_clked =0;
    }

    //simulate pin toggle
    txuartPIN = uarttx_per_clked ? (uart_txdata_clked >> (uarttx_per_cnt_clked>>SIM_UART_BIT_PER)) & 0x01 : 1;

    // communcate with faketxuart via IPC share memory
    if (uarttx_per_end_p){ //simulate uart tx done
        *txuart0_shmptr = uart_txdata_clked;
    }
    uart_txdata_clked = uart_txdata; //

    

}