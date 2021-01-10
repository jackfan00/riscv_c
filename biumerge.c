#include "biumerge.h"
#include "ifubussplit.h"
#include "lsubussplit.h"

//roundrobin
void arbitor2(BIT i_valid0, BIT i_valid1, BIT i_link0pri, 
        BIT *o_link0pri, BIT *o_valid)
{
    *o_valid =i_valid0 | i_valid1;
    //
    *o_link0pri = (i_valid0 & (!i_valid1)) ? 0 :
                  (i_valid0 & i_valid1 & i_link0pri) ? 0 :
                  !(i_valid0 | i_valid1) ? i_link0pri : 1
                  ;
}


//ifu2biu come from ifubussplit
//lsu2biu come from lsubussplit 
void biumerge()
{
    REG8 nxtwrapped_biumergeFIFO_widx;
    BIT oifupri_p;
    BIT o_cmd_valid_p;

    //ifu/lsu roundrobin
    //ifupri_clked : current ifu2biu_cmd_valid priority, 1:high, 0:low
    //oifupri_p : after arbitor, next time ifu2biu_cmd_valid priority
    arbitor2(ifu2biu_cmd_valid, lsu2biu_cmd_valid, biumerge_ifupri_clked, &oifupri_p, &o_cmd_valid_p);
    biumerge_o_cmd_valid = (o_cmd_valid_p);// & (!biumergeFIFOfull);
    biumerge_o_cmd_read   =  ((oifupri_p) ? lsu2biu_cmd_read   : ifu2biu_cmd_read  )   ;
    biumerge_o_cmd_adr    =  ((oifupri_p) ? lsu2biu_cmd_adr    : ifu2biu_cmd_adr   )   ;
    biumerge_o_cmd_data   =  ((oifupri_p) ? lsu2biu_cmd_data   : ifu2biu_cmd_data  )   ;
    biumerge_o_cmd_rwbyte =  ((oifupri_p) ? lsu2biu_cmd_rwbyte : ifu2biu_cmd_rwbyte)   ;

    //oifupri_p=0, select ifu, otherwise select lsu
    ifu2biu_cmd_ready = (!(oifupri_p)) & biumerge_o_cmd_ready;
    lsu2biu_cmd_ready = (oifupri_p) & biumerge_o_cmd_ready;

    //wid: 0:ifu, 1:lsu
    biumergeFIFO_wen = (biumerge_o_cmd_valid & biumerge_o_cmd_ready);// & biumerge_o_cmd_read);
    biumerge_ifupri = biumerge_o_cmd_valid & biumerge_o_cmd_ready ? oifupri_p : biumerge_ifupri_clked;
    biumergeFIFO_wid = biumerge_ifupri ? 1 : 0;
    biumergeFIFO = biumergeFIFO_wen ? biumergeFIFO_wid : biumergeFIFO_clked[biumergeFIFO_widx_clked];
    nxtwrapped_biumergeFIFO_widx = ((biumergeFIFO_widx_clked==(BIUMERGEFIFODEPTH-1)) ? 0 :  biumergeFIFO_widx_clked+1);
    biumergeFIFO_widx = biumergeFIFO_wen ? nxtwrapped_biumergeFIFO_widx : 
                            biumergeFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    biumergeFIFOfull = (nxtwrapped_biumergeFIFO_widx==biumergeFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    biumergeFIFOempty = //(biumergeFIFO_widx_clked==biumergeFIFO_ridx_clked);
                        (biumergeFIFO_widx_clked==biumergeFIFO_ridx_clked) & biumergeFIFO_ren & (!biumergeFIFO_wen);

    biumergeFIFO_rid =  //biumerge_o_cmd_valid & (!biumerge_o_cmd_read) ? biumergeFIFO_wid : //for write bypass
                        biumerge_o_cmd_valid & (!biumerge_o_cmd_read) & biumergeFIFOempty_clked ? biumergeFIFO_wid : //for write bypass
                        //biumergeFIFOempty ? biumergeFIFO_wid : 
                        biumergeFIFO_clked[biumergeFIFO_ridx_clked];

    //rsp accept and move biumergeFIFO_ridx to next item
    biumergeFIFO_ren = biumerge_o_rsp_valid & biumerge_o_rsp_ready;// & biumerge_o_rsp_read & 
                       // (biumerge_o_cmd_valid?biumerge_o_cmd_read:1);  //eliminate write case
    biumergeFIFO_ridx = biumergeFIFO_ren ? ((biumergeFIFO_ridx_clked==(BIUMERGEFIFODEPTH-1)) ? 0 :  biumergeFIFO_ridx_clked+1) : 
                            biumergeFIFO_ridx_clked;

    ifu2biu_rsp_read  = (!biumergeFIFO_rid) & biumerge_o_rsp_read;
    ifu2biu_rsp_valid = (!biumergeFIFO_rid) & biumerge_o_rsp_valid;
    ifu2biu_rsp_rdata = biumerge_o_rsp_rdata;
    lsu2biu_rsp_read  = ( biumergeFIFO_rid) & biumerge_o_rsp_read;
    lsu2biu_rsp_valid = ( biumergeFIFO_rid) & biumerge_o_rsp_valid;
    lsu2biu_rsp_rdata = biumerge_o_rsp_rdata;
    biumerge_o_rsp_ready = biumergeFIFO_rid ? lsu2biu_rsp_ready : ifu2biu_rsp_ready;


}


