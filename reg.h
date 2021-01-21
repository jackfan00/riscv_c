#ifndef REG_H
#define REG_H
typedef unsigned long long REG64;
typedef unsigned int REG32;
typedef unsigned short REG16;
typedef unsigned char REG8;
typedef unsigned char BIT;


#define ITCM_ADDR_BASE   0x80000000
#define DTCM_ADDR_BASE   0x90000000
 //   * PPI       : 0x1000 0000 -- 0x1FFF FFFF
#define PPI_ADDR_BASE    0x10000000
#define TXUART_ADDR      0x10013000
  //  * CLINT     : 0x0200 0000 -- 0x0200 FFFF
  //  * PLIC      : 0x0C00 0000 -- 0x0CFF FFFF
#define CLINT_ADDR_BASE  0x02000000
#define PLIC_ADDR_BASE   0x0C000000
#define FIO_ADDR_BASE    0xf0000000

#define PLIC_INTNUMBER  64  //
#define PLIC_INTNUMBER_REG32  2  // PLIC_INTNUMBER>>5


//#define DEPFIFOSIZE 4
#define RSPFIFOSIZE 2  //only support 2
#define CODEARBIT_NUM 4  //ifu(r), lsu(rw), debug(rw), downloadcode(rw)
#define DATAARBIT_NUM 4  //lsu(rw), debug(rw), downloadcode(rw)
#define WBARBIT_NUM 4   //lsu, div, mul, execu, debug

//regfile write: only memwb, read:only decode
#define REGARBIT_NUM 2  //memwb

#define MAXCODESIZE 65536
#define BOOTADDR ITCM_ADDR_BASE
#define RASDEPTH 8
#define LIFSIZE 8

//normal sram parameter is  (1, 0), DATARAM_RREADY_CYCLES=0 is not supported
//#define DATARAM_RSPVALID_CYCLES 1
//#define DATARAM_CMDREADY_CYCLES 0

//normal sram parameter is  (1, 0), CODERAM_RREADY_CYCLES=0 is not supported
//#define CODERAM_RSPVALID_CYCLES 1
//#define CODERAM_CMDREADY_CYCLES 0

//MUL cycles, MUL_RSPVALID_CYCLES=0 is not supportted
#define MUL_RSPVALID_CYCLES 1


#define BIUSPLITTARGETNUM 5
#define BIUSPLIFIFODEPTH 3
#define BIUMERGEFIFODEPTH 3
#define DTCMMERGEFIFODEPTH 3
#define IFUSPLITTARGETNUM 2
#define IFUSPLIFIFODEPTH 3
#define ITCMMERGEFIFODEPTH 3
#define LSUSPLITTARGETNUM 3
#define LSUSPLIFIFODEPTH 3
#define ITCMMERGEFIFODEPTH 3


//REG8 code_rspid_fifo[RSPFIFOSIZE];
//REG8 data_rspid_fifo[RSPFIFOSIZE];
REG32 clockcnt;
//REG32 coderam[MAXCODESIZE];
//REG8 dataram0[MAXCODESIZE];
//REG8 dataram1[MAXCODESIZE];
//REG8 dataram2[MAXCODESIZE];
//REG8 dataram3[MAXCODESIZE];
//REG8 depfifo[DEPFIFOSIZE];
//BIT depfifo_fg[DEPFIFOSIZE];
//REG32 regsarray[32];
REG32 ras_stack[RASDEPTH];
REG8 ras_sp;


//UART
#define MYKEY_UART0 25
#define BUFSIZE_UART0 16  //tx, rx
//REG32 * txuart0_shmptr;
//REG32 * rxuart0_shmptr;

#endif // REG_H

