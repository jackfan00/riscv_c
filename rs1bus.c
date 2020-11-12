#include <stdio.h>

#include "regbus.h"
#include "decode.h"
//


void rs1bus()
{

//local
REG8 rspid;
BIT or_grt, or_grt_clked;
BIT o_rs1bus_cmd_valid;
BIT o_rs1bus_cmd_ready;
REG32 o_rs1bus_cmd_adr;
REG32 o_rs1bus_rsp_rdata;
BIT o_rs1bus_rsp_valid;
BIT o_rs1bus_rsp_err;



int i,j;

    rs1bus_connect();

    // priority arbitor
    for(i=0; i<REGARBIT_NUM; i++){

        //
        //implement (|i_rs1bus_grt_clked[i+1:REGARBIT_NUM-1])
        or_grt_clked=0;
        for (j=i+1; j<REGARBIT_NUM; j++){
            or_grt_clked |= i_rs1bus_grt_clked[j];
        }
        //
        if (i==0){
            i_rs1bus_grt[i] = i_rs1bus_cmd_valid[i] & (!or_grt_clked);//!(|i_rs1bus_grt_clked[i+1:REGARBIT_NUM-1]);
        }
        else{
            //implement (|i_rs1bus_grt[i-1:0])
            or_grt=0;
            for (j=0; j<i; j++){
                or_grt |= i_rs1bus_grt[j];
            }
            i_rs1bus_grt[i] = (!or_grt) & i_rs1bus_cmd_valid[i] & (!or_grt_clked);//~(|i_rs1bus_grt[i-1:0]), !(|i_rs1bus_grt_clked[i+1:REGARBIT_NUM-1]);
        }
        //
        //selected initiator
        if (i_rs1bus_grt[i]){
            printf("INFO: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            //w_rspid = i;
            rspid = i;
            o_rs1bus_cmd_valid = 1; //(!rspid_fifo_full_clked);
            //o_rs1bus_cmd_read = 1; //i_rs1bus_cmd_read[i];
            o_rs1bus_cmd_adr = i_rs1bus_cmd_adr[i];
            //o_rs1bus_cmd_wdata = 0; //i_rs1bus_cmd_wdata[i];
            //o_rs1bus_cmd_rwbyte = 0xf; //i_rs1bus_cmd_rwbyte[i];
            i_rs1bus_cmd_ready[i] = o_rs1bus_cmd_ready ;//& (!rspid_fifo_full_clked);
        }
    }


    //
    o_rs1bus_cmd_ready =1;
    if (o_rs1bus_cmd_valid & o_rs1bus_cmd_ready){
        o_rs1bus_rsp_rdata = regsarray[o_rs1bus_cmd_adr];
        o_rs1bus_rsp_valid = 1;
        o_rs1bus_rsp_err =0;
    }
    else{
        o_rs1bus_rsp_valid = 0;
    }



    //rspid = rspid_fifo_empty_clked ? w_rspid : r_rspid;
    for(i=0; i<REGARBIT_NUM; i++){
        if (i==rspid){
            // printf("INFO: rsp arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            i_rs1bus_rsp_valid[i] = o_rs1bus_rsp_valid;
            i_rs1bus_rsp_err[i] = o_rs1bus_rsp_err;
            i_rs1bus_rsp_rdata[i] = o_rs1bus_rsp_rdata;
            //o_rs1bus_rsp_ready = i_rs1bus_rsp_ready[i];
            break;
        }

    }


    //
    //regrctrl();

}
/*
void regrctrl()
{
    o_rs1bus_cmd_ready =1;
    if (o_rs1bus_cmd_valid & o_rs1bus_cmd_ready){
        o_rs1bus_rsp_rdata = regsarray[o_rs1bus_cmd_adr];
        o_rs1bus_rsp_valid = 1;
        o_rs1bus_rsp_err =0;
    }
    else{
        o_rs1bus_rsp_valid = 0;
    }
    //

    //

}*/


