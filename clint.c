#include "clint.h"

void clint()
{
    REG64 t1,t2;

    //
    clint_cmd_ready = clint_cmd_valid & 1;
    clint_regcs = clint_cmd_valid & clint_cmd_ready ? 1 : 0;
    clint_regw = !clint_cmd_read;
    clint_regadr = clint_cmd_adr;
    clint_regwdata = clint_cmd_data;
    //
    clint_msip = clint_regcs & clint_regw & (clint_regadr==CLINT_MSIP) ? clint_regwdata : clint_msip_clked;
    clint_mtimecmp = clint_regcs & clint_regw & (clint_regadr==CLINT_MTIMECMP) ? clint_regwdata : clint_mtimecmp_clked;
    clint_mtimecmph = clint_regcs & clint_regw & (clint_regadr==CLINT_MTIMECMPH) ? clint_regwdata : clint_mtimecmph_clked;

    // hardware implematation NOTE: count at low freq clock
    clint_mtime = clint_regcs & clint_regw & (clint_regadr==CLINT_MTIME) ? clint_regwdata : clint_mtime_clked+1;
    clint_mtimeh = clint_regcs & clint_regw & (clint_regadr==CLINT_MTIMEH) ? clint_regwdata : 
                                (clint_mtime_clked==0xffffffff) ? clint_mtimeh_clked+1 : clint_mtimeh_clked;
    t1 = clint_mtimeh_clked;
    t1 = (t1<<32)|clint_mtime_clked;

    t2 = clint_mtimecmph_clked;
    t2 = (t2<<32)|clint_mtimecmp_clked;

    clint_mtip = (t1>=t2);

    //regrdata
    clint_rsp_rdata = 
                (clint_regadr==CLINT_MSIP) ? clint_msip_clked :
                (clint_regadr==CLINT_MTIMECMP) ? clint_mtimecmp_clked :
                (clint_regadr==CLINT_MTIMECMPH) ? clint_mtimecmph_clked :
                (clint_regadr==CLINT_MTIME) ? clint_mtime_clked :
                (clint_regadr==CLINT_MTIMEH) ? clint_mtimeh_clked : 0;

    clint_rsp_valid =  clint_regcs;

}