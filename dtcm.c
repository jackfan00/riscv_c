#include "dtcm.h"
#include "dtcmmerge.h"

void dtcm()
{
    BIT notready;
    //dtcmmerge_o_cmd_ready= (!dtcmmerge_o_rsp_valid | (dtcmmerge_o_rsp_valid & dtcmmerge_o_rsp_ready)) & dtcmmerge_o_cmd_valid;
    notready = 0;//dtcmRAM_wr & dtcmRAM_read_clked;
    //dtcmmerge_o_cmd_ready= dtcmmerge_o_rsp_ready & dtcmmerge_o_cmd_valid & (!notready);
    dtcmmerge_o_cmd_ready = (!dtcmmerge_o_rsp_read) | (dtcmmerge_o_rsp_read&dtcmmerge_o_rsp_ready);
    //
    dtcmRAM_cs = dtcmmerge_o_cmd_valid & dtcmmerge_o_cmd_ready;
    dtcmRAM_wr = !dtcmmerge_o_cmd_read;
    dtcmRAM_wdat = dtcmmerge_o_cmd_data;
    dtcmRAM_adr = dtcmmerge_o_cmd_adr;
    dtcmRAM_bmask = dtcmmerge_o_cmd_rwbyte;

    dtcmRAM_read = dtcmRAM_cs & (!dtcmRAM_wr) ? 1:
                   dtcmmerge_o_rsp_read&dtcmmerge_o_rsp_ready ? 0 :
                   //dtcmmerge_o_rsp_valid & dtcmmerge_o_rsp_ready & (dtcmmerge_o_cmd_valid ? dtcmmerge_o_cmd_read:1) ? 0 :  //eliminate write case
                   dtcmRAM_read_clked;

    dtcmRAM_write = dtcmRAM_cs  & (dtcmRAM_wr) ? 1: 0;

    dtcmmerge_o_rsp_valid = 
                            dtcmRAM_read_clked | dtcmRAM_write_clked ? 1 : 0;
    //dtcmmerge_o_rsp_valid = dtcmRAM_cs & dtcmRAM_wr ? 1 :  //combinational loop issue
    //                        dtcmRAM_read_clked ? 1 : 0;

    dtcmRAM_read1st = dtcmRAM_cs & (!dtcmRAM_wr) ? 1: 0;
    read_dtcmRAM_rdat = dtcmRAM_read1st_clked ? dtcmRAM_rdat : read_dtcmRAM_rdat_clked;

    dtcmmerge_o_rsp_rdata =  (dtcmRAM_read1st_clked ? dtcmRAM_rdat : read_dtcmRAM_rdat_clked)  ;

    //dtcmmerge_o_rsp_rdata = dtcmRAM_rdat;

    dtcmmerge_o_rsp_read = dtcmRAM_read_clked;

}