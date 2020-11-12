#ifndef MEMORYBUS_CLKED_H
#define MEMORYBUS_CLKED_H

//input
BIT i_bus_grt[CODEARBIT_NUM];
BIT rspid_fifo_wen;
BIT rspid_fifo_ren;
REG8 w_rspid;
REG32 rspid_fifo_wadr;
REG32 rspid_fifo_radr;

//output
REG8 r_rspid;
REG32 rspid_fifo_wadr_clked;
REG32 rspid_fifo_radr_clked;
BIT rspid_fifo_full_clked;
BIT rspid_fifo_empty_clked=1;
BIT i_bus_grt_clked[CODEARBIT_NUM];

#endif // MEMORYBUS_CLKED_H

