#include <stdio.h>

#include "reg.h"
//#include "memorybus_clked.h"
#include "databus.h"


void databus_clked()
{

//local


int i;
    //
    for (i=0;i<CODEARBIT_NUM;i++){
        i_databus_grt_clked[i] = i_databus_grt[i];
    }


    if (data_rspid_fifo_ren & data_rspid_fifo_empty_clked & (!data_rspid_fifo_wen)){
        printf("Error:fifo read empty\n");
    }
    if (data_rspid_fifo_wen & data_rspid_fifo_full_clked){
        printf("Error:fifo write full\n");
    }

    if (data_rspid_fifo_wen){
        data_rspid_fifo[data_rspid_fifo_wadr] = w_data_rspid;
        data_rspid_fifo_wadr_clked = data_rspid_fifo_wadr >= RSPFIFOSIZE-1 ? 0 : data_rspid_fifo_wadr+1;
        //data_rspid_fifo_full_clked = (data_rspid_fifo_wadr_clked==data_rspid_fifo_radr);
        data_rspid_fifo_empty_clked =0;
    }
    if (data_rspid_fifo_ren){
        r_data_rspid = data_rspid_fifo[data_rspid_fifo_radr];
        data_rspid_fifo_radr_clked = data_rspid_fifo_radr >= RSPFIFOSIZE-1 ? 0 :data_rspid_fifo_radr+1;
        //data_rspid_fifo_empty_clked = (data_rspid_fifo_wadr==data_rspid_fifo_radr_clked);
        data_rspid_fifo_full_clked =0;
    }

    //
    data_rspid_fifo_wadr = data_rspid_fifo_wadr_clked;
    data_rspid_fifo_radr = data_rspid_fifo_radr_clked;
    if (data_rspid_fifo_wen){
        data_rspid_fifo_full_clked = (data_rspid_fifo_wadr_clked==data_rspid_fifo_radr);
    }
    if (data_rspid_fifo_ren){
        data_rspid_fifo_empty_clked = (data_rspid_fifo_wadr==data_rspid_fifo_radr_clked);
    }

    //
    dataramctrl_clked();
}

void dataramctrl_clked()
{
    REG32 adr;
    REG8 rdat0;
    REG8 rdat1;
    REG8 rdat2;
    REG8 rdat3;
    REG8 wdat0;
    REG8 wdat1;
    REG8 wdat2;
    REG8 wdat3;
    REG8 adr01;

    //
    adr = (dataram_adr & 0x00ffffff);
    adr01 = adr & 0x03;
    adr =  adr >>2;
    rdat0 = dataram0[adr];
    rdat1 = dataram1[adr]<<8;
    rdat2 = dataram2[adr]<<16;
    rdat3 = dataram3[adr]<<24;
    dataram_rdat = rdat0 + rdat1 + rdat2 + rdat3;

    if (dataram_cs){
        if (dataram_we){
            wdat0 =dataram_wdat&0x0ff ;
            wdat1 =dataram_wdat&0x0ff00 ;
            wdat2 =dataram_wdat&0x0ff0000 ;
            wdat3 =dataram_wdat&0xff000000 ;
                           
            dataram_wdat = (adr01==1) ? (dataram_bmask==0x01 ? rdat3+rdat2+wdat1+rdat0 :
                                         dataram_bmask==0x03 ? rdat3+wdat2+wdat1+rdat0 : 
                                         wdat3+wdat2+wdat1+rdat0) :  //invalid case
                           (adr01==2) ? (dataram_bmask==0x01 ? rdat3+wdat2+rdat1+rdat0 :
                                         dataram_bmask==0x03 ? wdat3+wdat2+wdat1+rdat0 : 
                                         wdat3+wdat2+rdat1+rdat0) :  //invalid case
                           (adr01==3) ? (wdat3+rdat2+wdat1+rdat0) :   
                                        (dataram_bmask==0x01 ? rdat3+rdat2+rdat1+wdat0 :
                                         dataram_bmask==0x03 ? rdat3+rdat2+wdat1+wdat0 : 
                                         wdat3+wdat2+wdat1+wdat0) ;                          

            dataram0[adr] =   dataram_wdat & 0x0ff  ;
            dataram1[adr] =   (dataram_wdat>>8) & 0x0ff   ;
            dataram2[adr] =   (dataram_wdat>>16) & 0x0ff   ;
            dataram3[adr] =   (dataram_wdat>>24) & 0x0ff   ;
        }
        else{
            dataram_rdat = (adr01==1) ? dataram_rdat>>8 :
                           (adr01==2) ? dataram_rdat>>16 :
                           (adr01==3) ? dataram_rdat>>24 : dataram_rdat;
            dataram_rdat = (dataram_bmask==0x1) ? dataram_rdat & 0x0ff :
                           (dataram_bmask==0x3) ? dataram_rdat & 0x0ffff : dataram_rdat;           
        }
    }
    dataram_cs_clked = dataram_cs;
    dataram_we_clked = dataram_we;

}
