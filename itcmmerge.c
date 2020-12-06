#include "itcmmerge.h"
#include "ifubussplit.h"
#include "lsubussplit.h"

//roundrobin
void itcmarbitor2(BIT i_valid0, BIT i_valid1, BIT i_link0pri, 
        BIT *o_link0pri, BIT *o_valid)
{
    *o_valid =i_valid0 | i_valid1;
    //
    *o_link0pri = (i_valid0 & (!i_valid1)) ? 0 :
                  (i_valid0 & i_valid1 & i_link0pri) ? 0 :
                  !(i_valid0 | i_valid1) ? i_link0pri : 1
                  ;
}


//ifu2itcm come from ifubussplit
//lsu2itcm come from lsubussplit
//ext2itcm come from external  
void itcmmerge()
{
    REG8 nxtwrapped_itcmmergeFIFO_widx;
    BIT *arbitstage1_oifupri_p;
    BIT *arbitstage1_oifupri_p_o_cmd_valid_p;
    BIT *oifupri_p;
    BIT *o_cmd_valid_p;

    //ifu/lsu/ext roundrobin
    //ifupri_clked : current ifu2itcm_cmd_valid priority, 1:high, 0:low
    //oifupri_p : after arbitor, next time ifu2itcm_cmd_valid priority
    itcmarbitor2(ifu2itcm_cmd_valid, lsu2itcm_cmd_valid, itcmmerge_ifupri_clked, arbitstage1_oifupri_p, arbitstage1_oifupri_p_o_cmd_valid_p);
    
    itcmarbitor2(ext2itcm_cmd_valid, *arbitstage1_oifupri_p_o_cmd_valid_p, itcmmerge_extpri_clked, oifupri_p, o_cmd_valid_p);

    itcmmerge_o_cmd_valid = (*o_cmd_valid_p) & (!itcmmergeFIFOfull);
    itcmmerge_o_cmd_read = itcmmerge_o_cmd_valid ? ((*oifupri_p) ? ((*arbitstage1_oifupri_p) ? lsu2itcm_cmd_read:ifu2itcm_cmd_read) : ext2itcm_cmd_read) : 0;
    itcmmerge_o_cmd_adr  = itcmmerge_o_cmd_valid ? ((*oifupri_p) ? ((*arbitstage1_oifupri_p) ? lsu2itcm_cmd_adr :ifu2itcm_cmd_adr ) : ext2itcm_cmd_adr ) : 0;
    itcmmerge_o_cmd_data = itcmmerge_o_cmd_valid ? ((*oifupri_p) ? ((*arbitstage1_oifupri_p) ? lsu2itcm_cmd_data:ifu2itcm_cmd_data) : ext2itcm_cmd_data) : 0;
    itcmmerge_o_cmd_rwbyte = itcmmerge_o_cmd_valid ? ((*oifupri_p) ? ((*arbitstage1_oifupri_p) ? lsu2itcm_cmd_rwbyte:ifu2itcm_cmd_rwbyte) : ext2itcm_cmd_rwbyte) : 0;


    //*oifupri_p=0, select ifu, otherwise select lsu
    ifu2itcm_cmd_ready = (*oifupri_p) & (!(*arbitstage1_oifupri_p)) & itcmmerge_o_cmd_ready;
    lsu2itcm_cmd_ready = (*oifupri_p) & (*arbitstage1_oifupri_p)    & itcmmerge_o_cmd_ready;
    ext2itcm_cmd_ready =(!(*oifupri_p)) & itcmmerge_o_cmd_ready;

    //wid: 0:ifu, 1:lsu, 2:ext
    itcmmergeFIFO_wen = ((itcmmerge_o_cmd_valid) & itcmmerge_o_cmd_ready);
    itcmmerge_ifupri = itcmmergeFIFO_wen ? *arbitstage1_oifupri_p : itcmmerge_ifupri_clked;
    itcmmerge_extpri = itcmmergeFIFO_wen ? *oifupri_p : itcmmerge_extpri_clked;
    itcmmergeFIFO_wid = itcmmerge_extpri ? (itcmmerge_ifupri ? 1 : 0) : 2;

    itcmmergeFIFO = itcmmergeFIFO_wen ? itcmmergeFIFO_wid : itcmmergeFIFO_clked[itcmmergeFIFO_widx_clked];
    nxtwrapped_itcmmergeFIFO_widx = ((itcmmergeFIFO_widx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  itcmmergeFIFO_widx_clked+1);
    itcmmergeFIFO_widx = itcmmergeFIFO_wen ? nxtwrapped_itcmmergeFIFO_widx : 
                            itcmmergeFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    itcmmergeFIFOfull = (nxtwrapped_itcmmergeFIFO_widx==itcmmergeFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    itcmmergeFIFOempty = (itcmmergeFIFO_widx_clked==itcmmergeFIFO_ridx_clked);
    itcmmergeFIFO_rid = itcmmergeFIFOempty ? itcmmergeFIFO_wid : itcmmergeFIFO_clked[itcmmergeFIFO_ridx_clked];

    //rsp accept and move itcmmergeFIFO_ridx to next item
    itcmmergeFIFO_ren = itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready;
    itcmmergeFIFO_ridx = itcmmergeFIFO_ren ? ((itcmmergeFIFO_ridx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  itcmmergeFIFO_ridx_clked+1) : 
                            itcmmergeFIFO_ridx_clked;

    ifu2itcm_rsp_valid = (itcmmergeFIFO_rid==0) & itcmmerge_o_rsp_valid;
    ifu2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    lsu2itcm_rsp_valid = (itcmmergeFIFO_rid==1) & itcmmerge_o_rsp_valid;
    lsu2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    ext2itcm_rsp_valid = (itcmmergeFIFO_rid==2) & itcmmerge_o_rsp_valid;
    ext2itcm_rsp_rdata = itcmmerge_o_rsp_rdata;
    itcmmerge_o_rsp_ready = itcmmergeFIFO_rid==1 ? lsu2itcm_rsp_ready : 
                            itcmmergeFIFO_rid==0 ? ifu2itcm_rsp_ready :
                            itcmmergeFIFO_rid==2 ? ext2itcm_rsp_ready : 0
                            ;


}


