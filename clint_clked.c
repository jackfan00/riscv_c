#include <stdio.h>
#include "clint.h"

void clint_clked()
{
    //hclk_cnt_clked = clk32768_p ? 0 : hclk_cnt_clked+1;

    clint_msip_clked = clint_msip;
    clint_mtimecmp_clked = clint_mtimecmp;
    clint_mtimecmph_clked = clint_mtimecmph;
    clint_mtime_clked = clint_mtime;
    clint_mtimeh_clked = clint_mtimeh;
    //not reg
    clint_mtip_clked = clint_mtip;
    //if (clint_mtip_clked){
    //    printf("clint timer interrupt happen\n");
    //}

    clint_read_clked = clint_read;

    clint_write_clked = clint_write;
    clint_read1st_clked = clint_read1st;
    read_clint_rdat_clked = read_clint_rdat;
    clint_csadr_clked = clint_regcs ? clint_regwadr : clint_csadr_clked;

}