#ifndef MEMORYBUS_CLKED_H
#define MEMORYBUS_CLKED_H

//input
BIT i_databus_grt[CODEARBIT_NUM];
BIT data_rspid_fifo_wen;
BIT data_rspid_fifo_ren;
REG8 w_data_rspid;
REG32 data_rspid_fifo_wadr;
REG32 data_rspid_fifo_radr;

//output
REG8 r_data_rspid;
REG32 data_rspid_fifo_wadr_clked;
REG32 data_rspid_fifo_radr_clked;
BIT data_rspid_fifo_full_clked;
BIT data_rspid_fifo_empty_clked=1;
BIT i_databus_grt_clked[CODEARBIT_NUM];

#endif // MEMORYBUS_CLKED_H

