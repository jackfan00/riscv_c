#include "regfilemerge.h"
#include "execu.h"
#include "memwb.h"

//roundrobin
void regfilearbitor2(BIT i_valid0, BIT i_valid1, BIT i_link0pri, 
        BIT *o_link0pri, BIT *o_valid)
{
    *o_valid =i_valid0 | i_valid1;
    //
    *o_link0pri = (i_valid0 & (!i_valid1)) ? 0 :
                  (i_valid0 & i_valid1 & i_link0pri) ? 0 :
                  !(i_valid0 | i_valid1) ? i_link0pri : 1
                  ;
}


//div2regfile come from ifubussplit
//lsu2regfile come from lsubussplit
//mul2regfile come from external  
void regfilemerge()
{
    REG8 nxtwrapped_regfilemergeFIFO_widx;
    BIT arbitstage1_odivpri_p;
    BIT arbitstage1_omulpri_p;
    BIT arbitstage1_div_o_cmd_valid_p;
    BIT arbitstage1_mul_o_cmd_valid_p;
    BIT s2pri_p;
    BIT o_cmd_valid_p;

    //div/lsu/mul/memwb roundrobin
    //divpri_clked : current div2regfile_cmd_valid priority, 1:high, 0:low
    //mulpri_clked : current mul2regfile_cmd_valid priority, 1:high, 0:low
    //
    regfilearbitor2(div2regfile_cmd_valid, lsu2regfile_cmd_valid,   divpri_clked, &arbitstage1_odivpri_p, &arbitstage1_div_o_cmd_valid_p);
    regfilearbitor2(mul2regfile_cmd_valid, memwb2regfile_cmd_valid, mulpri_clked, &arbitstage1_omulpri_p, &arbitstage1_mul_o_cmd_valid_p);
    regfilearbitor2(arbitstage1_div_o_cmd_valid_p, arbitstage1_mul_o_cmd_valid_p, s2pri_clked, &s2pri_p, &o_cmd_valid_p);

    regfilemerge_o_cmd_valid = (o_cmd_valid_p) & (!regfilemergeFIFOfull);
    regfilemerge_o_cmd_read = regfilemerge_o_cmd_valid ? (
                                        !(s2pri_p) ? ((arbitstage1_odivpri_p) ? lsu2regfile_cmd_read : div2regfile_cmd_read) : 
                                                      ((arbitstage1_omulpri_p) ? memwb2regfile_cmd_read : mul2regfile_cmd_read)
                                                        ) :  0;
    regfilemerge_o_cmd_adr  = regfilemerge_o_cmd_valid ? (
                                        !(s2pri_p) ? ((arbitstage1_odivpri_p) ? lsu2regfile_cmd_adr : div2regfile_cmd_adr) : 
                                                     ((arbitstage1_omulpri_p) ? memwb2regfile_cmd_adr : mul2regfile_cmd_adr)
                                                        ) :  0;
    regfilemerge_o_cmd_data = regfilemerge_o_cmd_valid ? (
                                        !(s2pri_p) ? ((arbitstage1_odivpri_p) ? lsu2regfile_cmd_data : div2regfile_cmd_data) : 
                                                      ((arbitstage1_omulpri_p) ? memwb2regfile_cmd_data : mul2regfile_cmd_data)
                                                        ) :  0;
    regfilemerge_o_cmd_rwbyte = regfilemerge_o_cmd_valid ? (
                                        !(s2pri_p) ? ((arbitstage1_odivpri_p) ? lsu2regfile_cmd_rwbyte : div2regfile_cmd_rwbyte) : 
                                                     ((arbitstage1_omulpri_p) ? memwb2regfile_cmd_rwbyte : mul2regfile_cmd_rwbyte)
                                                        ) :  0;
                                                        

    //
    div2regfile_cmd_ready = (!(s2pri_p)) &  (!(arbitstage1_odivpri_p)) & regfilemerge_o_cmd_ready;
    lsu2regfile_cmd_ready = (!(s2pri_p)) &    (arbitstage1_odivpri_p)  & regfilemerge_o_cmd_ready;
    mul2regfile_cmd_ready =  ((s2pri_p))  & (!(arbitstage1_omulpri_p)) & regfilemerge_o_cmd_ready;
    memwb2regfile_cmd_ready= ((s2pri_p))  &  ((arbitstage1_omulpri_p)) & regfilemerge_o_cmd_ready;

    //wid: 0:div, 1:lsu, 2:mul, 3:memwb
    regfilemergeFIFO_wen = ((regfilemerge_o_cmd_valid) & regfilemerge_o_cmd_ready);
    //store three arbitor2 block priority value 
    //0 means current selected, so priority will change to 0(low) in next clock
    divpri = regfilemergeFIFO_wen ? arbitstage1_odivpri_p : divpri_clked;
    mulpri = regfilemergeFIFO_wen ? arbitstage1_omulpri_p : mulpri_clked;
    s2pri  = regfilemergeFIFO_wen ? s2pri_p : s2pri_clked;

    regfilemergeFIFO_wid =  (!s2pri) & (!divpri) ? 0 :  //div
                            (!s2pri) & ( divpri) ? 1 :  //lsu
                            ( s2pri) & (!divpri) ? 2 :  //mul
                                                   3 ;  //memwb

    regfilemergeFIFO = regfilemergeFIFO_wen ? regfilemergeFIFO_wid : regfilemergeFIFO_clked[regfilemergeFIFO_widx_clked];
    nxtwrapped_regfilemergeFIFO_widx = ((regfilemergeFIFO_widx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  regfilemergeFIFO_widx_clked+1);
    regfilemergeFIFO_widx = regfilemergeFIFO_wen ? nxtwrapped_regfilemergeFIFO_widx : 
                            regfilemergeFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    regfilemergeFIFOfull = (nxtwrapped_regfilemergeFIFO_widx==regfilemergeFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    regfilemergeFIFOempty = (regfilemergeFIFO_widx_clked==regfilemergeFIFO_ridx_clked);
    regfilemergeFIFO_rid = regfilemergeFIFOempty ? regfilemergeFIFO_wid : regfilemergeFIFO_clked[regfilemergeFIFO_ridx_clked];

    //rsp accept and move regfilemergeFIFO_ridx to next item
    regfilemergeFIFO_ren = regfilemerge_o_rsp_valid & regfilemerge_o_rsp_ready;
    regfilemergeFIFO_ridx = regfilemergeFIFO_ren ? ((regfilemergeFIFO_ridx_clked==(ITCMMERGEFIFODEPTH-1)) ? 0 :  regfilemergeFIFO_ridx_clked+1) : 
                            regfilemergeFIFO_ridx_clked;

    //
    div2regfile_rsp_valid = (regfilemergeFIFO_rid==0) & regfilemerge_o_rsp_valid;
    div2regfile_rsp_rdata = regfilemerge_o_rsp_rdata;
    lsu2regfile_rsp_valid = (regfilemergeFIFO_rid==1) & regfilemerge_o_rsp_valid;
    lsu2regfile_rsp_rdata = regfilemerge_o_rsp_rdata;
    mul2regfile_rsp_valid = (regfilemergeFIFO_rid==2) & regfilemerge_o_rsp_valid;
    mul2regfile_rsp_rdata = regfilemerge_o_rsp_rdata;
    memwb2regfile_rsp_valid = (regfilemergeFIFO_rid==3) & regfilemerge_o_rsp_valid;
    memwb2regfile_rsp_rdata = regfilemerge_o_rsp_rdata;

    regfilemerge_o_rsp_ready =  regfilemergeFIFO_rid==0 ? div2regfile_rsp_ready :
                                regfilemergeFIFO_rid==1 ? lsu2regfile_rsp_ready : 
                                regfilemergeFIFO_rid==2 ? mul2regfile_rsp_ready : 
                                regfilemergeFIFO_rid==3 ? memwb2regfile_rsp_ready : 0
                            ;

    regfile_wrdiv  = regfilemergeFIFO_wen & (regfilemergeFIFO_wid==0);
    regfile_wrload = regfilemergeFIFO_wen & (regfilemergeFIFO_wid==1);

}


