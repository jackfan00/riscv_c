#include <stdio.h>

#include "mapping.h"
#include "codebus.h"
//


void codebus()
{

//local
REG8 rspid;
BIT or_grt, or_grt_clked;

int i,j;

    codebus_connect();

    code_rspid_fifo_wadr = code_rspid_fifo_wadr_clked;
    code_rspid_fifo_radr = code_rspid_fifo_radr_clked;
    // priority arbitor
    o_codebus_cmd_valid =0;
    for(i=0; i<CODEARBIT_NUM; i++){

        //
        //implement (|i_codebus_grt_clked[i+1:ARBIT_NUM-1])
        or_grt_clked=0;
        for (j=i+1; j<CODEARBIT_NUM; j++){
            or_grt_clked |= i_codebus_grt_clked[j];
        }
        //
        if (i==0){
            i_codebus_grt[i] = i_codebus_cmd_valid[i] & (!or_grt_clked);//!(|i_codebus_grt_clked[i+1:ARBIT_NUM-1]);
        }
        else{
            //implement (|i_codebus_grt[i-1:0])
            or_grt=0;
            for (j=0; j<i; j++){
                or_grt |= i_codebus_grt[j];
            }
            i_codebus_grt[i] = (!or_grt) & i_codebus_cmd_valid[i] & (!or_grt_clked);//~(|i_codebus_grt[i-1:0]), !(|i_codebus_grt_clked[i+1:ARBIT_NUM-1]);
        }
        //
        //selected initiator
        if (i_codebus_grt[i]){
            //printf("codebus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            w_code_rspid = i;
            o_codebus_cmd_valid = 1; //(!code_rspid_fifo_full_clked);
            o_codebus_cmd_read = i_codebus_cmd_read[i];
            o_codebus_cmd_adr = i_codebus_cmd_adr[i];
            o_codebus_cmd_wdata = i_codebus_cmd_wdata[i];
            o_codebus_cmd_rwbyte = i_codebus_cmd_rwbyte[i];
            i_codebus_cmd_ready[i] = o_codebus_cmd_ready ; //& (!code_rspid_fifo_full_clked);
        }
    }


    r_code_rspid = code_rspid_fifo[code_rspid_fifo_radr];
    //rspid = code_rspid_fifo_empty_clked ? w_code_rspid : r_code_rspid;
    rspid = r_code_rspid;
    for(i=0; i<CODEARBIT_NUM; i++){
        if (i==rspid){
            // printf("codebus: rsp arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            i_codebus_rsp_valid[i] = o_codebus_rsp_valid;
            i_codebus_rsp_err[i] = o_codebus_rsp_err;
            i_codebus_rsp_rdata[i] = o_codebus_rsp_rdata;
            o_codebus_rsp_ready = i_codebus_rsp_ready[i];
            //break;
        }
        else{
            i_codebus_rsp_valid[i] = 0;
        //    i_codebus_rsp_err[i] = 0;
        //    i_codebus_rsp_rdata[i] = 0;
        //    o_codebus_rsp_ready = 0;
        }
    }

    //only read-request need to write rspid_fifo
    code_rspid_fifo_wen = o_codebus_cmd_valid & o_codebus_cmd_ready & o_codebus_cmd_read;
    code_rspid_fifo_ren = o_codebus_rsp_valid & o_codebus_rsp_ready;


    //address demux
    if ((o_codebus_cmd_adr&0xff000000)==ITCM_ADDR_BASE){
        coderamctrl();
    }
    //
    o_codebus_rsp_rdata = coderam_rdat;
    //o_codebus_rsp_valid = coderam_cs_clked & !coderam_we_clked;   
   
    //o_codebus_rsp_valid = coderam_wrsp_valid | coderam_rrsp_valid ;
    //only reply read-request response
    //o_codebus_rsp_valid =  coderam_rrsp_valid ;
    o_codebus_rsp_valid =  CODERAM_RSPVALID_CYCLES==0 ? o_codebus_cmd_valid & o_codebus_cmd_read : 
                      coderam_rrsp_per_clked & (coderam_rspvalid_cycles_clked>=CODERAM_RSPVALID_CYCLES) ;
    

}

void coderamctrl()
{
    //
    // cmd_ready consider the larger latency one of cmdready and rspvalid
    o_codebus_cmd_ready = CODERAM_CMDREADY_CYCLES==0 ? (!code_rspid_fifo_full_clked) |
                                (code_rspid_fifo_full_clked & o_codebus_rsp_valid & o_codebus_rsp_ready) : 
                          (coderam_cmdready_cycles_clked>=CODERAM_CMDREADY_CYCLES) & (
                 (!code_rspid_fifo_full_clked) | (code_rspid_fifo_full_clked & o_codebus_rsp_valid & o_codebus_rsp_ready)
                              );

    if (o_codebus_cmd_valid & o_codebus_cmd_ready){
        coderam_adr = (o_codebus_cmd_adr & 0x00ffffff) >>2;
        coderam_cs =1;
        coderam_we = !o_codebus_cmd_read;
        coderam_wdat = o_codebus_cmd_wdata;
        coderam_bmask = o_codebus_cmd_rwbyte;
    }
    else{
        coderam_cs = 0;
    }
    //
    
    //coderam_wrsp_valid = //CODERAM_WREADY_CYCLES==0 ? coderam_cs & coderam_we :
    //                     coderam_wrsp_per_clked & (ready_cycles_clked==CODERAM_WREADY_CYCLES);
    //coderam_rrsp_valid = //CODERAM_RREADY_CYCLES==0 ? coderam_cs & (!coderam_we):
    //                     coderam_rrsp_per_clked & (ready_cycles_clked==CODERAM_RREADY_CYCLES);

}


