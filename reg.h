#ifndef REG_H
#define REG_H
typedef unsigned int REG32;
typedef unsigned short REG16;
typedef unsigned char REG8;
typedef unsigned char BIT;


#define ITCM_ADDR_BASE   0x80000000
#define DTCM_ADDR_BASE   0 //0x90000000
 //   * PPI       : 0x1000 0000 -- 0x1FFF FFFF
#define PPI_ADDR_BASE  0x10000000
  //  * CLINT     : 0x0200 0000 -- 0x0200 FFFF
  //  * PLIC      : 0x0C00 0000 -- 0x0CFF FFFF
#define CLINT_ADDR_BASE  0x02000000
#define PLIC_ADDR_BASE   0x0C000000
#define FIO_ADDR_BASE    0xf0000000



#define DEPFIFOSIZE 4
#define RSPFIFOSIZE 4
#define CODEARBIT_NUM 4
#define DATAARBIT_NUM 4
#define REGARBIT_NUM 2
#define MAXCODESIZE 1024
#define BOOTADDR ITCM_ADDR_BASE
#define RASDEPTH 8

//normal sram parameter is  (1, 0), DATARAM_RREADY_CYCLES=0 is not supported
#define DATARAM_RREADY_CYCLES 1
#define DATARAM_WREADY_CYCLES 0

//normal sram parameter is  (1, 0), CODERAM_RREADY_CYCLES=0 is not supported
#define CODERAM_RREADY_CYCLES 1
#define CODERAM_WREADY_CYCLES 0


REG8 code_rspid_fifo[RSPFIFOSIZE];
REG8 data_rspid_fifo[RSPFIFOSIZE];
REG32 clockcnt;
REG32 coderam[MAXCODESIZE];
REG8 dataram0[MAXCODESIZE], dataram1[MAXCODESIZE], dataram2[MAXCODESIZE], dataram3[MAXCODESIZE];
//REG8 depfifo[DEPFIFOSIZE];
//BIT depfifo_fg[DEPFIFOSIZE];
REG32 regsarray[32];
REG32 ras_stack[RASDEPTH];
REG8 ras_sp;


BIT firstclk;

#endif // REG_H

