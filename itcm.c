#include "itcm.h"
#include "itcmmerge.h"

void itcm()
{
    itcmmerge_o_cmd_ready= (!itcmmerge_o_rsp_valid | (itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready)) & itcmmerge_o_cmd_valid;
    //
    itcmRAM_cs = itcmmerge_o_cmd_valid & itcmmerge_o_cmd_ready;
    itcmRAM_wr = !itcmmerge_o_cmd_read;
    itcmRAM_wdat = itcmmerge_o_cmd_data;
    itcmRAM_adr = itcmmerge_o_cmd_adr;
    itcmRAM_bmask = itcmmerge_o_cmd_rwbyte;

    itcmRAM_read = itcmRAM_cs & (!itcmRAM_wr) ? 1:
                   itcmmerge_o_rsp_valid & itcmmerge_o_rsp_ready ? 0 :
                   itcmRAM_read_clked;

    itcmmerge_o_rsp_valid = itcmRAM_cs & itcmRAM_wr ? 1 :
                            itcmRAM_read_clked ? 1 : 0;
    itcmmerge_o_rsp_rdata = itcmRAM_rdat;

}