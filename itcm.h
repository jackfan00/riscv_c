#ifndef ITCM_H
#define ITCM_H
void itcm();
void itcm_clked();

#include "reg.h"


REG32 itcmRAM0[MAXCODESIZE], itcmRAM1[MAXCODESIZE], itcmRAM2[MAXCODESIZE], itcmRAM3[MAXCODESIZE];

//
REG32 itcmRAM_csadr_clked;
BIT itcmRAM_read_clked;
REG32 read_itcmRAM_rdat_clked;
BIT itcmRAM_read1st_clked;

//
BIT   itcmRAM_cs;
BIT   itcmRAM_wr;
REG8  itcmRAM_bmask;
REG32 itcmRAM_adr;
REG32 itcmRAM_wdat;
REG32 itcmRAM_rdat;
BIT itcmRAM_read;
REG32 read_itcmRAM_rdat;
BIT itcmRAM_read1st;

#endif //ITCM_H
