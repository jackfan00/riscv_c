#include "regfile.h"
#include "regfilemerge.h"
#include "decode.h"

void regfile()
{

    //regfile write
    //ready should always 1
    regfilemerge_o_cmd_ready= (!regfilemerge_o_rsp_valid | (regfilemerge_o_rsp_valid & regfilemerge_o_rsp_ready)) & regfilemerge_o_cmd_valid;
    //
    regfileffs_cs = regfilemerge_o_cmd_valid & regfilemerge_o_cmd_ready;
    regfileffs_wr = !regfilemerge_o_cmd_read;  //should always 1
    regfileffs_wdat = regfilemerge_o_cmd_data;
    regfileffs_adr = regfilemerge_o_cmd_adr;
    //regfileffs_bmask = regfilemerge_o_cmd_rwbyte;
    regfilemerge_o_rsp_valid = regfileffs_cs;
    regfilemerge_o_rsp_rdata = 0;
    regfilemerge_o_rsp_read = 0;

    //regfile read , rs1, rs2
    //only from decode
    rs1v = regfileffs_clked[rs1idx];
    rs2v = regfileffs_clked[rs2idx];


}