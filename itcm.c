#include "itcm.h"
#include "itcmmerge.h"

void itcm()
{
    BIT notready;
    //itcmmerge_o_cmd_ready= (!itcmmerge_o_rsp_valid | (itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready)) & itcmmerge_o_cmd_valid;
    //notready = 0;//itcmRAM_wr & itcmRAM_read_clked;
    //itcmmerge_o_cmd_ready=  itcmmerge_o_rsp_ready & itcmmerge_o_cmd_valid & (!notready);
    //
    itcmmerge_o_cmd_ready = (!itcmmerge_o_rsp_read) | (itcmmerge_o_rsp_read&itcmmerge_o_rsp_ready);
    //
    itcmRAM_cs = itcmmerge_o_cmd_valid & itcmmerge_o_cmd_ready;
    itcmRAM_wr = !itcmmerge_o_cmd_read;
    itcmRAM_wdat = itcmmerge_o_cmd_data;
    itcmRAM_adr = itcmmerge_o_cmd_adr;
    itcmRAM_bmask = itcmmerge_o_cmd_rwbyte;

    itcmRAM_read = itcmRAM_cs  & (!itcmRAM_wr) ? 1:
                    itcmmerge_o_rsp_read&itcmmerge_o_rsp_ready ? 0 :
                   //itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready ? & (itcmmerge_o_cmd_valid ? itcmmerge_o_cmd_read :1) ? 0 :  //eliminate write case
                   itcmRAM_read_clked;
    
    itcmRAM_write = itcmRAM_cs  & (itcmRAM_wr) ? 1: 0;

    itcmmerge_o_rsp_valid = 
                            itcmRAM_read_clked | itcmRAM_write_clked ? 1 : 0;
                            //itcmRAM_cs & itcmRAM_wr ? 1 : 0; //combinational loop issue


    //only generate 1 cycle               
    //this is for solve lsu/ifu access dead-lock issue
    //additional read_itcmRAM_rdat_clked storage to store read-command itcmRAM_rdat
    itcmRAM_read1st = itcmRAM_cs & (!itcmRAM_wr) ? 1: 0;
    read_itcmRAM_rdat = itcmRAM_read1st_clked ? itcmRAM_rdat : read_itcmRAM_rdat_clked;

    itcmmerge_o_rsp_rdata =  (itcmRAM_read1st_clked ? itcmRAM_rdat : read_itcmRAM_rdat_clked)  ;

    itcmmerge_o_rsp_read = itcmRAM_read_clked;

}