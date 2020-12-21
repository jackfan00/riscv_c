#include "dtcm.h"

void dtcm_clked()
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
    REG32 tmp_rdat0;
    REG32 tmp_rdat1;
    REG32 tmp_rdat2;
    REG32 tmp_rdat3;
    REG32 tmp_adr01;
    
    //
    adr = (dtcmRAM_adr & 0x00ffffff);
    adr01 = adr & 0x03;
    adr =  adr >>2;
    rdat0 = dtcmRAM0[adr];
    rdat1 = dtcmRAM1[adr]<<8;
    rdat2 = dtcmRAM2[adr]<<16;
    rdat3 = dtcmRAM3[adr]<<24;
    //dtcmRAM_rdat = rdat0 + rdat1 + rdat2 + rdat3;

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

            dtcmRAM0[adr] =   dtcmRAM_wdat & 0x0ff  ;
            dtcmRAM1[adr] =   (dtcmRAM_wdat>>8) & 0x0ff   ;
            dtcmRAM2[adr] =   (dtcmRAM_wdat>>16) & 0x0ff   ;
            dtcmRAM3[adr] =   (dtcmRAM_wdat>>24) & 0x0ff   ;
        }
        //else{
        //    dtcmRAM_rdat = (adr01==1) ? dtcmRAM_rdat>>8 :
        //                   (adr01==2) ? dtcmRAM_rdat>>16 :
        //                   (adr01==3) ? dtcmRAM_rdat>>24 : dtcmRAM_rdat;
        //}

    }


    //dtcmRAM_csadr_clked = dtcmRAM_cs ? dtcmRAM_adr : dtcmRAM_csadr_clked;
    //dtcmRAM_read_clked = dtcmRAM_read;

    //tmpradr = (dtcmRAM_csadr_clked & 0x00ffffff)>>2;
    //dtcmRAM_rdat = (dtcmRAM3[tmpradr]<<24) | (dtcmRAM2[tmpradr]<<16) | (dtcmRAM1[tmpradr]<<8) | dtcmRAM0[tmpradr];


    dtcmRAM_csadr_clked = dtcmRAM_cs ? dtcmRAM_adr : dtcmRAM_csadr_clked;
    dtcmRAM_read_clked = dtcmRAM_read;
    dtcmRAM_write_clked = dtcmRAM_write;
    dtcmRAM_bmask_clked = dtcmRAM_cs ? dtcmRAM_bmask : dtcmRAM_bmask_clked;

    tmpradr = (dtcmRAM_csadr_clked & 0x00ffffff)>>2;

    tmp_rdat0 = dtcmRAM0[tmpradr];
    tmp_rdat1 = dtcmRAM1[tmpradr];
    tmp_rdat2 = dtcmRAM2[tmpradr];
    tmp_rdat3 = dtcmRAM3[tmpradr];
    tmp_adr01 = dtcmRAM_csadr_clked & 0x03;

    dtcmRAM_rdat = (tmp_adr01==0) ? (tmp_rdat3<<24)|(tmp_rdat2<<16)|(tmp_rdat1<<8)|tmp_rdat0 :
                    (tmp_adr01==1) ? (tmp_rdat3<<16)|(tmp_rdat2<<8)|tmp_rdat1 :
                    (tmp_adr01==2) ? (tmp_rdat3<<8)|tmp_rdat2 : 
                    tmp_rdat3;

    dtcmRAM_rdat =  dtcmRAM_bmask_clked==0x1 ? dtcmRAM_rdat & 0x0ff :
                    dtcmRAM_bmask_clked==0x3 ? dtcmRAM_rdat & 0x0ffff : 
                    dtcmRAM_bmask_clked==0x11 ? (dtcmRAM_rdat & 0x0ff  ) |  (dtcmRAM_rdat&0x80   ? 0xffffff00 : 0) : 
                    dtcmRAM_bmask_clked==0x13 ? (dtcmRAM_rdat & 0x0ffff) |  (dtcmRAM_rdat&0x8000 ? 0xffff0000 : 0) : 
                    dtcmRAM_rdat;

    dtcmRAM_read1st_clked = dtcmRAM_read1st;
    read_dtcmRAM_rdat_clked = read_dtcmRAM_rdat;

}
