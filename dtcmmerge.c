#include "dtcmmerge.h"
#include "ifubussplit.h"
#include "lsubussplit.h"

//roundrobin
void dtcmarbitor2(BIT i_valid0, BIT i_valid1, BIT i_link0pri, 
        BIT *o_link0pri, BIT *o_valid)
{
    *o_valid =i_valid0 | i_valid1;
    //
    *o_link0pri = (i_valid0 & (!i_valid1)) ? 0 :
                  (i_valid0 & i_valid1 & i_link0pri) ? 0 :
                  !(i_valid0 | i_valid1) ? i_link0pri : 1
                  ;
}


//lsu2dtcm come from lsubussplit
//ext2dtcm come from external  
void dtcmmerge()
{
    REG8 nxtwrapped_dtcmmergeFIFO_widx;
    BIT *oextpri_p;
    BIT *o_cmd_valid_p;

    //ext/lsu roundrobin
    //extpri_clked : current ext2dtcm_cmd_valid priority, 1:high, 0:low
    //oextpri_p : after arbitor, next time ext2dtcm_cmd_valid priority
    dtcmarbitor2(ext2dtcm_cmd_valid, lsu2dtcm_cmd_valid, dtcmmerge_extpri_clked, oextpri_p, o_cmd_valid_p);
    
    dtcmmerge_o_cmd_valid  = (*o_cmd_valid_p) & (!dtcmmergeFIFOfull);
    dtcmmerge_o_cmd_read   = dtcmmerge_o_cmd_valid ? ((*oextpri_p) ? lsu2dtcm_cmd_read  :ext2dtcm_cmd_read  )  : 0;
    dtcmmerge_o_cmd_adr    = dtcmmerge_o_cmd_valid ? ((*oextpri_p) ? lsu2dtcm_cmd_adr   :ext2dtcm_cmd_adr   )  : 0;
    dtcmmerge_o_cmd_data   = dtcmmerge_o_cmd_valid ? ((*oextpri_p) ? lsu2dtcm_cmd_data  :ext2dtcm_cmd_data  )  : 0;
    dtcmmerge_o_cmd_rwbyte = dtcmmerge_o_cmd_valid ? ((*oextpri_p) ? lsu2dtcm_cmd_rwbyte:ext2dtcm_cmd_rwbyte)  : 0;


    //*oextpri_p=0, select ifu, otherwise select lsu
    ext2dtcm_cmd_ready = (!(*oextpri_p)) &  dtcmmerge_o_cmd_ready;
    lsu2dtcm_cmd_ready = (*oextpri_p)    &  dtcmmerge_o_cmd_ready;

    //wid: 0:ext, 1:lsu, 
    dtcmmergeFIFO_wen = ((dtcmmerge_o_cmd_valid) & dtcmmerge_o_cmd_ready);
    dtcmmerge_extpri = dtcmmergeFIFO_wen ? *oextpri_p : dtcmmerge_extpri_clked;
    dtcmmergeFIFO_wid = dtcmmerge_extpri ? 1 : 0;

    dtcmmergeFIFO = dtcmmergeFIFO_wen ? dtcmmergeFIFO_wid : dtcmmergeFIFO_clked[dtcmmergeFIFO_widx_clked];
    nxtwrapped_dtcmmergeFIFO_widx = ((dtcmmergeFIFO_widx_clked==(DTCMMERGEFIFODEPTH-1)) ? 0 :  dtcmmergeFIFO_widx_clked+1);
    dtcmmergeFIFO_widx = dtcmmergeFIFO_wen ? nxtwrapped_dtcmmergeFIFO_widx : 
                            dtcmmergeFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    dtcmmergeFIFOfull = (nxtwrapped_dtcmmergeFIFO_widx==dtcmmergeFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    dtcmmergeFIFOempty = (dtcmmergeFIFO_widx_clked==dtcmmergeFIFO_ridx_clked);
    dtcmmergeFIFO_rid = dtcmmergeFIFOempty ? dtcmmergeFIFO_wid : dtcmmergeFIFO_clked[dtcmmergeFIFO_ridx_clked];

    //rsp accept and move dtcmmergeFIFO_ridx to next item
    dtcmmergeFIFO_ren = dtcmmerge_o_rsp_valid & dtcmmerge_o_rsp_ready;
    dtcmmergeFIFO_ridx = dtcmmergeFIFO_ren ? ((dtcmmergeFIFO_ridx_clked==(DTCMMERGEFIFODEPTH-1)) ? 0 :  dtcmmergeFIFO_ridx_clked+1) : 
                            dtcmmergeFIFO_ridx_clked;

    ext2dtcm_rsp_valid = (dtcmmergeFIFO_rid==0) & dtcmmerge_o_rsp_valid;
    ext2dtcm_rsp_rdata = dtcmmerge_o_rsp_rdata;
    lsu2dtcm_rsp_valid = (dtcmmergeFIFO_rid==1) & dtcmmerge_o_rsp_valid;
    lsu2dtcm_rsp_rdata = dtcmmerge_o_rsp_rdata;
    dtcmmerge_o_rsp_ready = dtcmmergeFIFO_rid==1 ? lsu2dtcm_rsp_ready : 
                            dtcmmergeFIFO_rid==0 ? ext2dtcm_rsp_ready : 0
                            ;


}


