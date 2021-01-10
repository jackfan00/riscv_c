#include "peripheral.h"
#include "uart.h"

//this is FAKED peripheral device
void peripheral()
{


    //peripheral_cmd_ready = (!peripheral_rsp_read) | (peripheral_rsp_read&peripheral_rsp_ready);
    peripheral_cmd_ready = (!peripheral_rsp_valid) | (peripheral_rsp_valid&peripheral_rsp_ready);

    peripheral_regcs = peripheral_cmd_valid & peripheral_cmd_ready;// ? 1 : 0;
    peripheral_regwr = !peripheral_cmd_read;
    peripheral_regwadr = peripheral_cmd_adr;
    //peripheral_regradr = peripheral_regcs & (!peripheral_regw) ? peripheral_cmd_adr : peripheral_csadr_clked;
    peripheral_regwdata = peripheral_cmd_data;
    //
    device_reg = peripheral_regcs & peripheral_regwr ? peripheral_regwdata : device_reg_clked;
    peripheral_rdat = uart_rsp_valid ? uart_rsp_rdata :
                    device_reg;


    peripheral_read =    peripheral_regcs & (!peripheral_regwr) ? 1 : 
                    peripheral_read_clked&peripheral_rsp_ready ? 0 :
                    //peripheral_rsp_valid & peripheral_rsp_ready & (peripheral_cmd_valid ? peripheral_cmd_read:1)? 0 :
                    peripheral_read_clked;

    peripheral_write = peripheral_regcs  & (peripheral_regwr) ? 1: 
                       peripheral_write_clked& peripheral_rsp_ready ? 0 :
                       peripheral_write_clked;

    peripheral_rsp_valid = uart_rsp_valid |
                            peripheral_read_clked | peripheral_write_clked ? 1 : 0;
                        //peripheral_regcs & peripheral_regw? 1 : //combinational loop issue
                        //peripheral_read_clked;
    peripheral_read1st = peripheral_regcs & (!peripheral_regwr) ? 1: 0;
    read_peripheral_rdat = peripheral_read1st_clked ? peripheral_rdat : read_peripheral_rdat_clked;

    peripheral_rsp_rdata =  (peripheral_read1st_clked ? peripheral_rdat : read_peripheral_rdat_clked)  ;

    peripheral_rsp_read =  peripheral_read_clked;



    //txUART
    txuart0_wr = peripheral_regcs & peripheral_regwr & UART0_TXDATA(peripheral_cmd_adr);
    txuart0_char = peripheral_regwdata & 0xff;

    uart_cmd_valid = peripheral_cmd_valid & UART0(peripheral_cmd_adr);
    uart_cmd_read  = uart_cmd_valid ? peripheral_cmd_read :0;
    uart_cmd_adr   = uart_cmd_valid ? peripheral_cmd_adr  :0;
    uart_cmd_data  = uart_cmd_valid ? peripheral_cmd_data :0;
    uart_rsp_ready = 1;

}

