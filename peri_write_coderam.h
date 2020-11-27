#ifndef PERI_WRITE_CODERAM_H
#define PERI_WRITE_CODERAM_H
#include "reg.h"

//input
BIT peri_cmd_ready;
BIT randomcycle_clked;
BIT downloadper_clked;
REG32 codeindex_clked;
REG32 download_codesize;

//output
BIT downloadstart;
BIT downloadcomplete;
BIT peri_cmd_valid;
BIT peri_cmd_read;
REG32 peri_cmd_addr;
REG32 peri_cmd_wdata;

#endif //PERI_WRITE_CODERAM_H