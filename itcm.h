#ifndef ITCM_H
#define ITCM_H
#include "reg.h"


REG8 itcmRAM0[MAXCODESIZE], itcmRAM1[MAXCODESIZE], itcmRAM2[MAXCODESIZE], itcmRAM3[MAXCODESIZE];

//
BIT itcmRAM_read_clked;

//
BIT   itcmRAM_cs;
BIT   itcmRAM_wr;
REG8  itcmRAM_bmask;
REG32 itcmRAM_adr;
REG32 itcmRAM_wdat;
REG32 itcmRAM_rdat;
BIT itcmRAM_read;

#endif //ITCM_H
