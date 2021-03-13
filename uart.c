#include "uart.h"
#include "simhw/simuart.h"

void uart()
{
//    uart_cmd_ready = (!uart_rsp_read) | (uart_rsp_read&uart_rsp_ready);
    uart_cmd_ready = (!uart_rsp_valid) | (uart_rsp_valid&uart_rsp_ready);

    uart_regcs = uart_cmd_valid & uart_cmd_ready;// ? 1 : 0;
    uart_regw = !uart_cmd_read;
    uart_regwadr = uart_cmd_adr;
    uart_regwdata = uart_cmd_data;
    //
    uart_txctrl = uart_regcs & uart_regw & (uart_regwadr==UART_TXCTRL) ? uart_regwdata : uart_txctrl_clked;
    uart_rxctrl = uart_regcs & uart_regw & (uart_regwadr==UART_RXCTRL) ? uart_regwdata : uart_rxctrl_clked;
    uart_ie = uart_regcs & uart_regw & (uart_regwadr==UART_IE) ? uart_regwdata : uart_ie_clked;
    uart_div = uart_regcs & uart_regw & (uart_regwadr==UART_DIV) ? uart_regwdata : uart_div_clked;

    uart_wr_txdata = uart_regcs & uart_regw & (uart_regwadr==UART_TXDATA);
    txdata_head = uart_wr_txdata ? (txdata_head_clked==7 ? 0 : txdata_head_clked+1) : 
                    txdata_head_clked;
    //simulate uart tx done            
    uarttx_per_end_p = (uarttx_per_cnt_clked==((uart_div_clked+1)*10)); //SIM_UART_TX_PER);
    txdata_tail = uarttx_per_end_p ? (txdata_tail_clked==7 ? 0 : txdata_tail_clked+1 ) : 
                    txdata_tail_clked;

    uart_txdata = uart_wr_txdata & (txdata_head==txdata_tail_clked) ? //full case
                //(1<<31)|(uart_regwdata&0x0ff) : 
                (1<<31) : 
                uarttx_per_end_p ? 0 : uart_txdata_clked;
                //uarttx_per_end_p ? 0 :   //simulate uart tx done
                //uart_txdata_clked; 

    //simulate uart rx done            
    uartrx_per_end_p = (uartrx_per_cnt_clked==((uart_div_clked+1)*10));//SIM_UART_TX_PER);
    rxdata_head = uartrx_per_end_p ? (rxdata_head_clked==7 ? 0 : rxdata_head_clked+1) : 
                    rxdata_head_clked;
    //incr tail when not empty                
    rxdata_tail = rxuart_done & (uart_rxdata_clked==0) ? (rxdata_tail_clked==7 ? 0 : rxdata_tail_clked+1 ) : 
                    rxdata_tail_clked;

    uart_rxdata = rxuart_done & (rxdata_tail==rxdata_head_clked) ? (1<<31) : //empty
                    uartrx_per_end_p ? 0 : uart_rxdata_clked;

    txcnt = txdata_head_clked>=txdata_tail_clked ? txdata_head_clked-txdata_tail_clked :
                8+txdata_head_clked-txdata_tail_clked;
    uart_txip =  txcnt < ((uart_txctrl_clked>>16)&0x7)  ? 1 : 0;        

    rxcnt = rxdata_head_clked>=rxdata_tail_clked ? rxdata_head_clked-rxdata_tail_clked :
                8+rxdata_head_clked-rxdata_tail_clked;
    uart_rxip =  rxcnt > ((uart_rxctrl_clked>>16)&0x7)  ? 1 : 0;       

    uart_intr =  (uart_txip_clked & (uart_ie_clked&0x1)) | 
                 (uart_rxip_clked & ((uart_ie_clked>>1)&0x1));

    //regrdata
    uart_rdat = 
                (uart_csadr_clked==UART_TXCTRL) ? uart_txctrl_clked :
                (uart_csadr_clked==UART_RXCTRL) ? uart_rxctrl_clked :
                (uart_csadr_clked==UART_IE) ? uart_ie_clked :
                (uart_csadr_clked==UART_IP) ? (uart_txip_clked|(uart_rxip_clked<<1)) :
                (uart_csadr_clked==UART_DIV) ? uart_div_clked :
                (uart_csadr_clked==UART_TXDATA) ? uart_txdata_clked :
                (uart_csadr_clked==UART_RXDATA) ? uart_rxdata_clked|uart_rxbuf_clked[rxdata_tail] : //*rxuart0_shmptr :
                 0;
    //been readout
    rxuart_done = (uart_csadr_clked==UART_RXDATA) & uart_rsp_valid & uart_rsp_ready;

    uart_read =    uart_regcs & (!uart_regw) ? 1 : 
                    uart_read_clked&uart_rsp_ready ? 0 :
                    //uart_rsp_valid & uart_rsp_ready & (uart_cmd_valid ? uart_cmd_read:1)? 0 :
                    uart_read_clked;

    uart_write = uart_regcs  & (uart_regw) ? 1: 
                       uart_write_clked& uart_rsp_ready ? 0 :
                       uart_write_clked;
    

    uart_rsp_valid = 
                            uart_read_clked | uart_write_clked ? 1 : 0;
                        //uart_regcs & uart_regw? 1 : //combinational loop issue
                        //uart_read_clked;
    uart_read1st = uart_regcs & (!uart_regw) ? 1: 0;
    read_uart_rdat = uart_read1st_clked ? uart_rdat : read_uart_rdat_clked;

    uart_rsp_rdata =  (uart_read1st_clked ? uart_rdat : read_uart_rdat_clked)  ;

    uart_rsp_read =  uart_read_clked;    
}