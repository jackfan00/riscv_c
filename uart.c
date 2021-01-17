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

    uart_wr_txdata = uart_regcs & uart_regw & (uart_regwadr==UART_TXDATA);
    uart_txdata = uart_wr_txdata ? 
                (1<<31)|(uart_regwdata&0x0ff) : 
                uarttx_per_end_p ? 0 :   //simulate uart tx done
                uart_txdata_clked; 

    //regrdata
    uart_rdat = 
                (uart_csadr_clked==UART_TXDATA) ? uart_txdata_clked :
                (uart_csadr_clked==UART_RXDATA) ? uart_rxdata_clked : //*rxuart0_shmptr :
                 0;
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