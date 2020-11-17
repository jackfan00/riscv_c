#include <stdio.h>

#include "regbus.h"
#include "decode.h"
//


void regwbus()
{

//local
REG8 rspid;
BIT or_grt, or_grt_clked;
BIT o_regwbus_cmd_valid;
BIT o_regwbus_cmd_ready;
REG32 o_regwbus_cmd_adr;
REG32 o_regwbus_cmd_wdata;
REG8 o_regwbus_cmd_id;


int i,j;

    o_regwbus_cmd_ready =1;
    o_regwbus_cmd_valid = 0;
    regwbus_connect();

    // priority arbitor
    for(i=0; i<REGARBIT_NUM; i++){

        //
        //implement (|i_regwbus_grt_clked[i+1:REGARBIT_NUM-1])
        or_grt_clked=0;
        for (j=i+1; j<REGARBIT_NUM; j++){
            or_grt_clked |= i_regwbus_grt_clked[j];
        }
        //
        if (i==0){
            i_regwbus_grt[i] = i_regwbus_cmd_valid[i] & (!or_grt_clked);//!(|i_regwbus_grt_clked[i+1:REGARBIT_NUM-1]);
        }
        else{
            //implement (|i_regwbus_grt[i-1:0])
            or_grt=0;
            for (j=0; j<i; j++){
                or_grt |= i_regwbus_grt[j];
            }
            i_regwbus_grt[i] = (!or_grt) & i_regwbus_cmd_valid[i] & (!or_grt_clked);//~(|i_regwbus_grt[i-1:0]), !(|i_regwbus_grt_clked[i+1:REGARBIT_NUM-1]);
        }
        //
        //selected initiator
        if (i_regwbus_grt[i]){
            //printf("INFO: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
            o_regwbus_cmd_valid = 1; //(!rspid_fifo_full_clked);
            o_regwbus_cmd_id = i_regwbus_cmd_id[i]; //i_regwbus_cmd_read[i];
            o_regwbus_cmd_adr = i_regwbus_cmd_adr[i];
            o_regwbus_cmd_wdata = i_regwbus_cmd_wdata[i];
            //o_regwbus_cmd_rwbyte = 0xf; //i_regwbus_cmd_rwbyte[i];
            //i_regwbus_cmd_ready[i] = o_regwbus_cmd_ready ;
        }
        //
        i_regwbus_cmd_ready[i] = 1 ;  //should always ready
        
    }

    //
    regw_cs =0;
    if (o_regwbus_cmd_valid & o_regwbus_cmd_ready){
        regw_adr = o_regwbus_cmd_adr;
        regw_cs = 1;
        regw_we = 1; //!o_regwbus_cmd_read;
        regw_wdat = o_regwbus_cmd_wdata;
        regw_id = o_regwbus_cmd_id;
    }
    //
    //regwctrl();


}

/*
void regwctrl()
{
    o_regwbus_cmd_ready =1;
    if (o_regwbus_cmd_valid & o_regwbus_cmd_ready){
        regw_adr = o_regwbus_cmd_adr;
        regw_cs = 1;
        regw_we = !o_regwbus_cmd_read;
        regw_wdat = o_regwbus_cmd_wdata;
    }
    //
}*/


