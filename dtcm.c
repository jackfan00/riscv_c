#include "dtcm.h"
#include "dtcmmerge.h"

void dtcm()
{
    dtcmmerge_o_cmd_ready= (!dtcmmerge_o_rsp_valid | (dtcmmerge_o_rsp_valid & dtcmmerge_o_rsp_ready)) & dtcmmerge_o_cmd_valid;
    //
    dtcmRAM_cs = dtcmmerge_o_cmd_valid & dtcmmerge_o_cmd_ready;
    dtcmRAM_wr = !dtcmmerge_o_cmd_read;
    dtcmRAM_wdat = dtcmmerge_o_cmd_data;
    dtcmRAM_adr = dtcmmerge_o_cmd_adr;
    dtcmRAM_bmask = dtcmmerge_o_cmd_rwbyte;

    dtcmRAM_read = dtcmRAM_cs & (!dtcmRAM_wr) ? 1:
                   dtcmmerge_o_rsp_valid & dtcmmerge_o_rsp_ready ? 0 :
                   dtcmRAM_read_clked;

    dtcmmerge_o_rsp_valid = dtcmRAM_cs & dtcmRAM_wr ? 1 :
                            dtcmRAM_read_clked ? 1 : 0;
    dtcmmerge_o_rsp_rdata = dtcmRAM_rdat;

}