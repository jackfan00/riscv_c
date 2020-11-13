#include <stdio.h>

#include "mapping.h"
#include "databus.h"
//


void databus()
{

//local
REG8 rspid;
BIT or_grt, or_grt_clked;

int i,j;

    databus_connect();

    data_rspid_fifo_wadr = data_rspid_fifo_wadr_clked;
    data_rspid_fifo_radr = data_rspid_fifo_radr_clked;
    // priority arbitor
    for(i=0; i<CODEARBIT_NUM; i++){

        //
        //implement (|i_databus_grt_clked[i+1:ARBIT_NUM-1])
        or_grt_clked=0;
        for (j=i+1; j<CODEARBIT_NUM; j++){
            or_grt_clked |= i_databus_grt_clked[j];
        }
        //
        if (i==0){
            i_databus_grt[i] = i_databus_cmd_valid[i] & (!or_grt_clked);//!(|i_databus_grt_clked[i+1:ARBIT_NUM-1]);
        }
        else{
            //implement (|i_databus_grt[i-1:0])
            or_grt=0;
            for (j=0; j<i; j++){
                or_grt |= i_databus_grt[j];
            }
            i_databus_grt[i] = (!or_grt) & i_databus_cmd_valid[i] & (!or_grt_clked);//~(|i_databus_grt[i-1:0]), !(|i_databus_grt_clked[i+1:ARBIT_NUM-1]);
        }
        //
        //selected initiator
        if (i_databus_grt[i]){
            //printf("INFO: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            w_data_rspid = i;
            o_databus_cmd_valid = (!data_rspid_fifo_full_clked);
            o_databus_cmd_read = i_databus_cmd_read[i];
            o_databus_cmd_adr = i_databus_cmd_adr[i];
            o_databus_cmd_wdata = i_databus_cmd_wdata[i];
            o_databus_cmd_rwbyte = i_databus_cmd_rwbyte[i];
            i_databus_cmd_ready[i] = o_databus_cmd_ready & (!data_rspid_fifo_full_clked);
        }
    }



    rspid = data_rspid_fifo_empty_clked ? w_data_rspid : r_data_rspid;
    for(i=0; i<CODEARBIT_NUM; i++){
        if (i==rspid){
            // printf("INFO: rsp arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            i_databus_rsp_valid[i] = o_databus_rsp_valid;
            i_databus_rsp_err[i] = o_databus_rsp_err;
            i_databus_rsp_rdata[i] = o_databus_rsp_rdata;
            o_databus_rsp_ready = i_databus_rsp_ready[i];
            break;
        }
        //else{
        //    i_databus_rsp_valid[i] = 0;
        //    i_databus_rsp_err[i] = 0;
        //    i_databus_rsp_rdata[i] = 0;
        //    o_databus_rsp_ready = 0;
        //}
    }


    data_rspid_fifo_wen = o_databus_cmd_valid & o_databus_cmd_ready;
    data_rspid_fifo_ren = o_databus_rsp_valid & o_databus_rsp_ready;


    //address demux
    if ((o_databus_cmd_adr&0xff000000)==DTCM_ADDR_BASE){
        dataramctrl();
    }

}

void dataramctrl()
{
    o_databus_cmd_ready =1;
    if (o_databus_cmd_valid & o_databus_cmd_ready){
        dataram_adr = (o_databus_cmd_adr); // & 0x00ffffff) >>2;
        dataram_cs =1;
        dataram_we = !o_databus_cmd_read;
        dataram_wdat = o_databus_cmd_wdata;
        dataram_bmask = o_databus_cmd_rwbyte;
    }
    //
    o_databus_rsp_rdata = dataram_rdat;
    o_databus_rsp_valid = dataram_cs_clked & !dataram_we_clked;
    //
    o_databus_rsp_err =0;
}


