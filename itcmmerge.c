#include "itcmmerge.h"
#include "ifubussplit.h"
#include "lsubussplit.h"

//
void itcmarbitor2(BIT i_valid0, BIT i_valid1, BIT i_link0pri, 
        BIT *o_link0pri, BIT *o_valid)
{
    *o_valid =i_valid0 | i_valid1;
    //roundrobin
    //*o_link0pri = (i_valid0 & (!i_valid1)) ? 0 :
    //              (i_valid0 & i_valid1 & i_link0pri) ? 0 :
    //              !(i_valid0 | i_valid1) ? i_link0pri : 1
    //              ;

    //valid1 is priority
    *o_link0pri = i_valid1 ? 1 : 
                  i_valid0 ? 0 :  i_link0pri ;

}


//different from dtcmmerge, we can not stall lsu, or will deadlock ifu-fetch
//for solve lsu access itcmRAM conflict with ifu-fetch and deadlock issue
//we need to have lsu own high priority 
//we need 1 additional REG32 to store itcmRAM_rdata

//ifu2itcm come from ifubussplit
//lsu2itcm come from lsubussplit
//ext2itcm come from external  
void itcmmerge()
{
    REG8 nxtwrapped_itcmmergeFIFO_widx;
    BIT arbitstage1_oifupri_p;
    BIT arbitstage1_oifupri_p_o_cmd_valid_p;
    BIT oifupri_p;
    BIT o_cmd_valid_p;

    //ifu/lsu/ext roundrobin
    //ifupri_clked : current ifu2itcm_cmd_valid priority, 1:high, 0:low
    //oifupri_p : after arbitor, next time ifu2itcm_cmd_valid priority
    itcmarbitor2(ifu2itcm_cmd_valid, lsu2itcm_cmd_valid, itcmmerge_ifupri_clked, &arbitstage1_oifupri_p, &arbitstage1_oifupri_p_o_cmd_valid_p);
    
    itcmarbitor2(ext2itcm_cmd_valid, arbitstage1_oifupri_p_o_cmd_valid_p, itcmmerge_extpri_clked, &oifupri_p, &o_cmd_valid_p);
    
    //here different from dtcmmerge
    itcmmerge_o_cmd_valid  = (o_cmd_valid_p) ;//& ((!itcmmergeFIFOfull) | (itcmmergeFIFO_ren));
    itcmmerge_o_cmd_read   = ((oifupri_p) ? ((arbitstage1_oifupri_p) ? lsu2itcm_cmd_read:ifu2itcm_cmd_read)     : ext2itcm_cmd_read)     ;
    itcmmerge_o_cmd_adr    = ((oifupri_p) ? ((arbitstage1_oifupri_p) ? lsu2itcm_cmd_adr :ifu2itcm_cmd_adr )     : ext2itcm_cmd_adr )     ;
    itcmmerge_o_cmd_data   = ((oifupri_p) ? ((arbitstage1_oifupri_p) ? lsu2itcm_cmd_data:ifu2itcm_cmd_data)     : ext2itcm_cmd_data)     ;
    itcmmerge_o_cmd_rwbyte = ((oifupri_p) ? ((arbitstage1_oifupri_p) ? lsu2itcm_cmd_rwbyte:ifu2itcm_cmd_rwbyte) : ext2itcm_cmd_rwbyte)   ;


    //*oifupri_p=0, select ifu, otherwise select lsu
    ifu2itcm_cmd_ready =  (oifupri_p) & (!(arbitstage1_oifupri_p)) & itcmmerge_o_cmd_ready;
    lsu2itcm_cmd_ready =  (oifupri_p) &   (arbitstage1_oifupri_p)  & itcmmerge_o_cmd_ready;
    ext2itcm_cmd_ready =(!(oifupri_p)) & itcmmerge_o_cmd_ready;

    //wid: 0:ifu, 1:lsu, 2:ext
    itcmmergeFIFO_wen = (itcmmerge_o_cmd_valid & itcmmerge_o_cmd_ready);// & itcmmerge_o_cmd_read);
    itcmmerge_ifupri = itcmmerge_o_cmd_valid & itcmmerge_o_cmd_ready ? arbitstage1_oifupri_p : itcmmerge_ifupri_clked;
    itcmmerge_extpri = itcmmerge_o_cmd_valid & itcmmerge_o_cmd_ready ? oifupri_p             : itcmmerge_extpri_clked;
    itcmmergeFIFO_wid = itcmmerge_extpri ? (itcmmerge_ifupri ? 1 : 0) : 2;

    itcmmergeFIFO_ren = itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready ;//& itcmmerge_o_rsp_read & 
                        //(itcmmerge_o_cmd_valid?itcmmerge_o_cmd_read:1) ; //eliminate write case
    //if write/read same time, write have high priority
    itcmmergeFIFO = itcmmergeFIFO_wen ? itcmmergeFIFO_wid : 
                    //itcmmergeFIFO_ren ? 0xff : 
                    itcmmergeFIFO_clked[itcmmergeFIFO_widx_clked];
    nxtwrapped_itcmmergeFIFO_widx = ((itcmmergeFIFO_widx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  itcmmergeFIFO_widx_clked+1);
    itcmmergeFIFO_widx = itcmmergeFIFO_wen ? nxtwrapped_itcmmergeFIFO_widx : 
                            itcmmergeFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    itcmmergeFIFOfull = (nxtwrapped_itcmmergeFIFO_widx==itcmmergeFIFO_ridx_clked);
                        // (itcmmergeFIFO_clked!=0xff); //


    //fifo empty definition : if current write-idx equal to current read-idx
    itcmmergeFIFOempty =// !itcmmergeFIFOfull; //
                        (itcmmergeFIFO_widx_clked==itcmmergeFIFO_ridx_clked) & itcmmergeFIFO_ren & (!itcmmergeFIFO_wen);
                        //(nxtwrapped_itcmmergeFIFO_widx==itcmmergeFIFO_ridx_clked);
    itcmmergeFIFO_rid = //itcmmerge_o_cmd_valid & (!itcmmerge_o_cmd_read) ? itcmmergeFIFO_wid : //for write bypass
                        itcmmerge_o_cmd_valid & (!itcmmerge_o_cmd_read) & itcmmergeFIFOempty_clked ? itcmmergeFIFO_wid : //for write bypass
                        itcmmergeFIFO_clked[itcmmergeFIFO_ridx_clked];

    //rsp accept and move itcmmergeFIFO_ridx to next item
    itcmmergeFIFO_ridx = itcmmergeFIFO_ren ? ((itcmmergeFIFO_ridx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  itcmmergeFIFO_ridx_clked+1) : 
                            itcmmergeFIFO_ridx_clked;

    ifu2itcm_rsp_read  = (itcmmergeFIFO_rid==0) & itcmmerge_o_rsp_read;
    ifu2itcm_rsp_valid = (itcmmergeFIFO_rid==0) & itcmmerge_o_rsp_valid;
    ifu2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    lsu2itcm_rsp_read  = (itcmmergeFIFO_rid==1) & itcmmerge_o_rsp_read;
    lsu2itcm_rsp_valid = (itcmmergeFIFO_rid==1) & itcmmerge_o_rsp_valid;
    lsu2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    ext2itcm_rsp_read  = (itcmmergeFIFO_rid==2) & itcmmerge_o_rsp_read;
    ext2itcm_rsp_valid = (itcmmergeFIFO_rid==2) & itcmmerge_o_rsp_valid;
    ext2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    itcmmerge_o_rsp_ready = itcmmergeFIFO_rid==1 ? lsu2itcm_rsp_ready : 
                            itcmmergeFIFO_rid==0 ? ifu2itcm_rsp_ready :
                            itcmmergeFIFO_rid==2 ? ext2itcm_rsp_ready : 1
                            ;


}


