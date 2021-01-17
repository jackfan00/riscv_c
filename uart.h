#ifndef UART_H
#define UART_H
#include "reg.h"
void uart();
void uart_clked();


#define UART_TXDATA         0x10013000
#define UART_RXDATA         0x10013004

//input
REG32 uart_txdata_clked;
REG32 uart_rxdata_clked;
BIT uart_read_clked;
//REG32 uart_regradr_clked;
BIT uart_write_clked;
BIT uart_read1st_clked;
REG32 read_uart_rdat_clked;
REG32 uart_csadr_clked;

//output
REG32 uart_txdata;
REG32 uart_rxdata;
BIT uart_regcs;
BIT uart_regw;
REG32 uart_regwdata;
REG32 uart_regwadr;
REG32 uart_regradr;
BIT uart_cmd_valid;
BIT uart_cmd_ready;
BIT uart_cmd_read;
REG32 uart_cmd_adr;
REG32 uart_cmd_data;
BIT uart_rsp_valid;
BIT uart_rsp_ready;
BIT uart_rsp_read;
REG32 uart_rsp_rdata;
BIT uart_read;
REG32 uart_rdat;
BIT uart_write;
BIT uart_read1st;
REG32 read_uart_rdat;
BIT rxuart_done;
BIT uart_wr_txdata;
//
//simulate
BIT uarttx_per_end_p;
REG32 uarttx_per_cnt_clked;
BIT uarttx_per_clked;
BIT txuartPIN;
REG32 uartrx_per_cnt_clked;
BIT uartrx_per_end_p;
BIT uartrx_per_clked;
REG32 uart_rxdata_tmp;
BIT rxuartPIN;

#endif //UART_H