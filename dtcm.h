#ifndef DTCM_H
#define DTCM_H
#include "reg.h"
void dtcm();
void dtcm_clked();


REG32 dtcmRAM0[MAXCODESIZE], dtcmRAM1[MAXCODESIZE], dtcmRAM2[MAXCODESIZE], dtcmRAM3[MAXCODESIZE];

//
BIT dtcmRAM_read_clked;
REG32 dtcmRAM_csadr_clked;
BIT dtcmRAM_write_clked;
REG32 read_dtcmRAM_rdat_clked;
BIT dtcmRAM_read1st_clked;
REG8 dtcmRAM_bmask_clked;

//
BIT   dtcmRAM_cs;
BIT   dtcmRAM_wr;
REG8  dtcmRAM_bmask;
REG32 dtcmRAM_adr;
REG32 dtcmRAM_wdat;
REG32 dtcmRAM_rdat;
BIT dtcmRAM_read;
BIT dtcmRAM_write;
REG32 read_dtcmRAM_rdat;
BIT dtcmRAM_read1st;

#endif //DTCM_H
