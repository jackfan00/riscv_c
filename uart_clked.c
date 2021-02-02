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
    uartrx_per_end_p = (uartrx_per_cnt_clked==((uart_div_clked+1)*10));//SIM_UART_TX_PER);
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
    rxuartPIN = uartrx_per_clked ? (uart_rxdata_tmp >> (uartrx_per_cnt_clked>>10)) & 0x01 : 1;
    //rxuartPIN = uartrx_per_clked ? (uart_rxdata_tmp >> (uartrx_per_cnt_clked>>SIM_UART_BIT_PER)) & 0x01 : 1;
    //if (uartrx_per_clked){
    //    printf("%x-%d:%d\n",uart_rxdata_tmp,uartrx_per_cnt_clked,rxuartPIN);
    //}    

    //check uart rxbuffer
    if (uartrx_per_end_p){  //simulate rx uart done
        //uart_rxdata_clked = uart_rxdata_tmp;
        uart_rxbuf_clked[rxdata_head] = uart_rxdata_tmp;
    }
    //else if (rxuart_done){
    //        uart_rxdata_clked=(1<<31);
    //}
    uart_rxdata_clked = uart_rxdata;

    //
    //simulate uart tx , 8N1 (startbit,8bit,stopbit)
    uarttx_per_end_p = (uarttx_per_cnt_clked==((uart_div_clked+1)*10)); //SIM_UART_TX_PER);
    txdata_empty = (txdata_head_clked==txdata_tail_clked) & (uart_txdata_clked==0);
    uarttx_per_cnt_clked = //uart_wr_txdata ? 0:
                            (uart_txctrl_clked&0x1) &(!txdata_empty) ? (uarttx_per_end_p ? 0 : uarttx_per_cnt_clked+1) :
                            //uarttx_per_clked ? uarttx_per_cnt_clked+1 :
                            0;
    
    uarttx_per_clked = (uart_txctrl_clked&0x1) &(!txdata_empty);
    //if (uart_wr_txdata){
    //    uarttx_per_clked = 1;
    //}
    //else if (uarttx_per_end_p){
    //    uarttx_per_clked =0;
    //}

    //simulate pin toggle
    txuartPIN = uarttx_per_clked ? (uart_txbuf_clked[txdata_tail_clked] >> (uarttx_per_cnt_clked>>7)) & 0x01 : 1;
    //txuartPIN = uarttx_per_clked ? (uart_txdata_clked >> (uarttx_per_cnt_clked>>SIM_UART_BIT_PER)) & 0x01 : 1;

    // communcate with faketxuart via IPC share memory
    if (uarttx_per_end_p){ //simulate uart tx done
        *txuart0_shmptr = uart_txbuf_clked[txdata_head_clked] | (1<<31);//uart_txdata_clked;
        printf("uarttxdone:%d, head:%d, tail:%d\n",clockcnt,txdata_head_clked, txdata_tail_clked);
    }
    uart_txdata_clked = uart_txdata; //
    uart_txbuf_clked[txdata_head] = uart_wr_txdata ? uart_regwdata : uart_txbuf_clked[txdata_head];
    
    uart_txip_clked = uart_txip;
    uart_rxip_clked = uart_rxip;
    uart_intr_clked = uart_intr;
    uart_txctrl_clked = uart_txctrl;
    uart_rxctrl_clked = uart_rxctrl;
    uart_ie_clked = uart_ie;
    uart_div_clked = uart_div;
    txdata_head_clked = txdata_head;
    txdata_tail_clked = txdata_tail;
    rxdata_head_clked = rxdata_head;
    rxdata_tail_clked = rxdata_tail;


}