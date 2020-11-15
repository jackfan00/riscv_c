#include <stdio.h>

#include "reg.h"
//#include "memorybus_clked.h"
#include "databus.h"


void databus_clked()
{

//local
REG8 nxt_wadr;
REG8 nxt_radr;

int i;
    //
    for (i=0;i<CODEARBIT_NUM;i++){
        if (i_databus_grt[i]){
            //printf("databus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
        i_databus_grt_clked[i] = i_databus_grt[i];
    }


    if (data_rspid_fifo_ren & data_rspid_fifo_empty_clked & (!data_rspid_fifo_wen)){
        printf("databus Error:fifo read empty\n");
    }
    if (data_rspid_fifo_wen & data_rspid_fifo_full_clked  & (!data_rspid_fifo_ren)){
        printf("databus Error:fifo write full\n");
    }

    if (data_rspid_fifo_wen){
        data_rspid_fifo[data_rspid_fifo_wadr] = w_data_rspid;
        data_rspid_fifo_wadr_clked = data_rspid_fifo_wadr >= RSPFIFOSIZE-1 ? 0 : data_rspid_fifo_wadr+1;
        //data_rspid_fifo_full_clked = (data_rspid_fifo_wadr_clked==data_rspid_fifo_radr);
        data_rspid_fifo_empty_clked =0;
    }
    if (data_rspid_fifo_ren){
        //r_data_rspid = data_rspid_fifo[data_rspid_fifo_radr];
        data_rspid_fifo_radr_clked = data_rspid_fifo_radr >= RSPFIFOSIZE-1 ? 0 :data_rspid_fifo_radr+1;
        //data_rspid_fifo_empty_clked = (data_rspid_fifo_wadr==data_rspid_fifo_radr_clked);
        data_rspid_fifo_full_clked =0;
    }

    //
    nxt_wadr = data_rspid_fifo_wadr_clked >= RSPFIFOSIZE-1 ? 0 : data_rspid_fifo_wadr_clked+1;
    nxt_radr = data_rspid_fifo_radr_clked >= RSPFIFOSIZE-1 ? 0 : data_rspid_fifo_radr_clked+1;
    //if (data_rspid_fifo_wen){
        data_rspid_fifo_full_clked = (nxt_wadr==data_rspid_fifo_radr_clked);
    //}
    //if (data_rspid_fifo_ren){
        data_rspid_fifo_empty_clked = (nxt_radr==data_rspid_fifo_wadr_clked);
    //}

    //
    dataramctrl_clked();
}

void dataramctrl_clked()
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

//
    //if (dataram_wrsp_valid){
    //    dataram_wrsp_per_clked = 0; 
    //}
    if (o_databus_rsp_valid){
        dataram_rrsp_per_clked = 0; 
    }        
    //
    if (o_databus_cmd_valid & o_databus_cmd_ready){
        dataram_cmdready_cycles_clked=0;
    }
    else if (o_databus_cmd_valid){
        dataram_cmdready_cycles_clked++;
    }
    else{
        dataram_cmdready_cycles_clked=0;
    }    

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
            dataram_wrsp_per_clked = 1;
            wdat0 =dataram_wdat&0x0ff ;
            wdat1 =(dataram_wdat>>8)&0x0ff ;
            wdat2 =(dataram_wdat>>16)&0x0ff ;
            wdat3 =(dataram_wdat>>24)&0xff ;
                           
            dataram_wdat = (adr01==1) ? (dataram_bmask==0x01 ? rdat3+rdat2+(wdat0<<8)+rdat0 :
                                         dataram_bmask==0x03 ? rdat3+(wdat1<<16)+(wdat0<<8)+rdat0 : 
                                         wdat2+wdat1+wdat0+rdat0) :  //invalid case
                           (adr01==2) ? (dataram_bmask==0x01 ? rdat3+(wdat0<<16)+rdat1+rdat0 :
                                         dataram_bmask==0x03 ? (wdat1<<24)+(wdat0<<16)+rdat1+rdat0 : 
                                         wdat1+wdat0+rdat1+rdat0) :  //invalid case
                           (adr01==3) ? (wdat0<<24)+rdat2+rdat1+rdat0 :  //only dataram_bmask==0x01 is valid case
                                        //(adr01==0) all valid case
                                        (dataram_bmask==0x01 ? rdat3+rdat2+rdat1+wdat0 :
                                         dataram_bmask==0x03 ? rdat3+rdat2+(wdat1<<8)+wdat0 : 
                                         dataram_wdat) ;                          

            dataram0[adr] =   dataram_wdat & 0x0ff  ;
            dataram1[adr] =   (dataram_wdat>>8) & 0x0ff   ;
            dataram2[adr] =   (dataram_wdat>>16) & 0x0ff   ;
            dataram3[adr] =   (dataram_wdat>>24) & 0x0ff   ;
        }
        else{
            dataram_rrsp_per_clked = 1;
            dataram_rdat = (adr01==1) ? dataram_rdat>>8 :
                           (adr01==2) ? dataram_rdat>>16 :
                           (adr01==3) ? dataram_rdat>>24 : dataram_rdat;
            //dataram_rdat = (dataram_bmask==0x1) ? dataram_rdat & 0x0ff :
            //               (dataram_bmask==0x3) ? dataram_rdat & 0x0ffff : dataram_rdat;           
        }
        dataram_rspvalid_cycles_clked = 1;

    }
    else if (dataram_rrsp_per_clked){
        dataram_rspvalid_cycles_clked++;
    }

    //dataram_cs_clked = dataram_cs;
    //dataram_we_clked = dataram_we;

}
