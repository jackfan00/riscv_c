#include "itcm.h"

void itcm_clked()
{
    REG32 adr;
    REG32 tmpradr;
    REG32 rdat0;
    REG32 rdat1;
    REG32 rdat2;
    REG32 rdat3;
    REG32 wdat0;
    REG32 wdat1;
    REG32 wdat2;
    REG32 wdat3;
    REG32 adr01;

    //
    adr = (itcmRAM_adr & 0x00ffffff);
    adr01 = adr & 0x03;
    adr =  adr >>2;
    rdat0 = itcmRAM0[adr];
    rdat1 = itcmRAM1[adr]<<8;
    rdat2 = itcmRAM2[adr]<<16;
    rdat3 = itcmRAM3[adr]<<24;

    if (itcmRAM_cs){
        if (itcmRAM_wr){
            wdat0 =itcmRAM_wdat&0x0ff ;
            wdat1 =(itcmRAM_wdat>>8)&0x0ff ;
            wdat2 =(itcmRAM_wdat>>16)&0x0ff ;
            wdat3 =(itcmRAM_wdat>>24)&0xff ;
                           
            itcmRAM_wdat = (adr01==1) ? (itcmRAM_bmask==0x01 ? rdat3+rdat2+(wdat0<<8)+rdat0 :
                                         itcmRAM_bmask==0x03 ? rdat3+(wdat1<<16)+(wdat0<<8)+rdat0 : 
                                         (wdat2<<24)+(wdat1<<16)+wdat0+rdat0) :  //invalid case
                           (adr01==2) ? (itcmRAM_bmask==0x01 ? rdat3+(wdat0<<16)+rdat1+rdat0 :
                                         itcmRAM_bmask==0x03 ? (wdat1<<24)+(wdat0<<16)+rdat1+rdat0 : 
                                         (wdat1<<24)+(wdat0<<16)+rdat1+rdat0) :  //invalid case
                           (adr01==3) ? (wdat0<<24)+rdat2+rdat1+rdat0 :  //only itcmRAM_bmask==0x01 is valid case
                                        //(adr01==0) all valid case
                                        (itcmRAM_bmask==0x01 ? rdat3+rdat2+rdat1+wdat0 :
                                         itcmRAM_bmask==0x03 ? rdat3+rdat2+(wdat1<<8)+wdat0 : 
                                         itcmRAM_wdat) ;                          

            itcmRAM0[adr] =   itcmRAM_wdat & 0x0ff  ;
            itcmRAM1[adr] =   (itcmRAM_wdat>>8) & 0x0ff   ;
            itcmRAM2[adr] =   (itcmRAM_wdat>>16) & 0x0ff   ;
            itcmRAM3[adr] =   (itcmRAM_wdat>>24) & 0x0ff   ;
        }
        //else{
        //    itcmRAM_rdat = (adr01==1) ? itcmRAM_rdat>>8 :
        //                   (adr01==2) ? itcmRAM_rdat>>16 :
        //                   (adr01==3) ? itcmRAM_rdat>>24 : itcmRAM_rdat;
        //}

    }


    itcmRAM_csadr_clked = itcmRAM_cs ? itcmRAM_adr : itcmRAM_csadr_clked;
    itcmRAM_read_clked = itcmRAM_read;

    tmpradr = itcmRAM_csadr_clked>>2;
    itcmRAM_rdat = (itcmRAM3[tmpradr]<<24) | (itcmRAM2[tmpradr]<<16) | (itcmRAM1[tmpradr]<<8) | itcmRAM0[tmpradr];

}
