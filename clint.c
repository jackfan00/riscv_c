#include "clint.h"

void clint()
{
    REG64 t1,t2;

    //
    //clint_cmd_ready = clint_cmd_valid & (!clint_rsp_valid | (clint_rsp_valid & clint_rsp_ready));
    //clint_cmd_ready = clint_cmd_valid & clint_rsp_ready;
    //clint_cmd_ready = (!clint_rsp_read) | (clint_rsp_read&clint_rsp_ready);
    clint_cmd_ready = (!clint_rsp_valid) | (clint_rsp_valid&clint_rsp_ready);

    clint_regcs = clint_cmd_valid & clint_cmd_ready;// ? 1 : 0;
    clint_regw = !clint_cmd_read;
    clint_regwadr = clint_cmd_adr;
    //clint_regradr = clint_regcs & (!clint_regw) ? clint_cmd_adr : clint_csadr_clked;
    clint_regwdata = clint_cmd_data;
    //
    clint_msip = clint_regcs & clint_regw & (clint_regwadr==CLINT_MSIP) ? clint_regwdata : clint_msip_clked;
    clint_mtimecmp = clint_regcs & clint_regw & (clint_regwadr==CLINT_MTIMECMP) ? clint_regwdata : clint_mtimecmp_clked;
    clint_mtimecmph = clint_regcs & clint_regw & (clint_regwadr==CLINT_MTIMECMPH) ? clint_regwdata : clint_mtimecmph_clked;

    // hardware implematation NOTE: count at always-on low freq clock
    clk32768_p = (hclk_cnt_clked==HCLK32768NUMBER);
    clint_mtime = clint_regcs & clint_regw & (clint_regwadr==CLINT_MTIME) ? clint_regwdata : 
                    clk32768_p ? clint_mtime_clked+1 : clint_mtime_clked;
    clint_mtimeh = clint_regcs & clint_regw & (clint_regwadr==CLINT_MTIMEH) ? clint_regwdata : 
                          clk32768_p & (clint_mtime_clked==0xffffffff) ? clint_mtimeh_clked+1 : clint_mtimeh_clked;
    t1 = clint_mtimeh_clked;
    t1 = (t1<<32)|clint_mtime_clked;

    t2 = clint_mtimecmph_clked;
    t2 = (t2<<32)|clint_mtimecmp_clked;

    clint_mtip = (t1>=t2);

    //regrdata
    clint_rdat = 
                (clint_csadr_clked==CLINT_MSIP) ? clint_msip_clked :
                (clint_csadr_clked==CLINT_MTIMECMP) ? clint_mtimecmp_clked :
                (clint_csadr_clked==CLINT_MTIMECMPH) ? clint_mtimecmph_clked :
                (clint_csadr_clked==CLINT_MTIME) ? clint_mtime_clked :
                (clint_csadr_clked==CLINT_MTIMEH) ? clint_mtimeh_clked : 0;

    clint_read =    clint_regcs & (!clint_regw) ? 1 : 
                    clint_read_clked&clint_rsp_ready ? 0 :
                    //clint_rsp_valid & clint_rsp_ready & (clint_cmd_valid ? clint_cmd_read:1)? 0 :
                    clint_read_clked;

    //clint_write = clint_regcs  & (clint_regw) ? 1: 0;
    clint_write = clint_regcs  & (clint_regw) ? 1: 
                       clint_write_clked& clint_rsp_ready ? 0 :
                       clint_write_clked;

    clint_rsp_valid = 
                            clint_read_clked | clint_write_clked ? 1 : 0;
                        //clint_regcs & clint_regw? 1 : //combinational loop issue
                        //clint_read_clked;
    clint_read1st = clint_regcs & (!clint_regw) ? 1: 0;
    read_clint_rdat = clint_read1st_clked ? clint_rdat : read_clint_rdat_clked;

    clint_rsp_rdata =  (clint_read1st_clked ? clint_rdat : read_clint_rdat_clked)  ;

    clint_rsp_read =  clint_read_clked;

}