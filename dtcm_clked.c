#include "dtcm.h"

void dtcm_clked()
{
    REG32 adr;
    REG32 rdat0;
    REG32 rdat1;
    REG32 rdat2;
    REG32 rdat3;
    REG32 wdat0;
    REG32 wdat1;
    REG32 wdat2;
    REG32 wdat3;
    REG32 adr01;
    REG32 dtcmRAM_rdat;

    //
    adr = (dtcmRAM_adr & 0x00ffffff);
    adr01 = adr & 0x03;
    adr =  adr >>2;
    rdat0 = dtcmRAM0[adr];
    rdat1 = dtcmRAM1[adr]<<8;
    rdat2 = dtcmRAM2[adr]<<16;
    rdat3 = dtcmRAM3[adr]<<24;
    dtcmRAM_rdat = rdat0 + rdat1 + rdat2 + rdat3;

    if (dtcmRAM_cs){
        if (dtcmRAM_wr){
            wdat0 =dtcmRAM_wdat&0x0ff ;
            wdat1 =(dtcmRAM_wdat>>8)&0x0ff ;
            wdat2 =(dtcmRAM_wdat>>16)&0x0ff ;
            wdat3 =(dtcmRAM_wdat>>24)&0xff ;
                           
            dtcmRAM_wdat = (adr01==1) ? (dtcmRAM_bmask==0x01 ? rdat3+rdat2+(wdat0<<8)+rdat0 :
                                         dtcmRAM_bmask==0x03 ? rdat3+(wdat1<<16)+(wdat0<<8)+rdat0 : 
                                         (wdat2<<24)+(wdat1<<16)+wdat0+rdat0) :  //invalid case
                           (adr01==2) ? (dtcmRAM_bmask==0x01 ? rdat3+(wdat0<<16)+rdat1+rdat0 :
                                         dtcmRAM_bmask==0x03 ? (wdat1<<24)+(wdat0<<16)+rdat1+rdat0 : 
                                         (wdat1<<24)+(wdat0<<16)+rdat1+rdat0) :  //invalid case
                           (adr01==3) ? (wdat0<<24)+rdat2+rdat1+rdat0 :  //only dtcmRAM_bmask==0x01 is valid case
                                        //(adr01==0) all valid case
                                        (dtcmRAM_bmask==0x01 ? rdat3+rdat2+rdat1+wdat0 :
                                         dtcmRAM_bmask==0x03 ? rdat3+rdat2+(wdat1<<8)+wdat0 : 
                                         dtcmRAM_wdat) ;                          

            dataram0[adr] =   dtcmRAM_wdat & 0x0ff  ;
            dataram1[adr] =   (dtcmRAM_wdat>>8) & 0x0ff   ;
            dataram2[adr] =   (dtcmRAM_wdat>>16) & 0x0ff   ;
            dataram3[adr] =   (dtcmRAM_wdat>>24) & 0x0ff   ;
        }
        else{
            dtcmRAM_rdat = (adr01==1) ? dtcmRAM_rdat>>8 :
                           (adr01==2) ? dtcmRAM_rdat>>16 :
                           (adr01==3) ? dtcmRAM_rdat>>24 : dtcmRAM_rdat;
        }

    }

    dtcmRAM_read_clked = dtcmRAM_read;


}
