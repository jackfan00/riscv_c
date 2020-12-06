#include "clint.h"

void clint_clked()
{
    clint_msip_clked = clint_msip;
    clint_mtimecmp_clked = clint_mtimecmp;
    clint_mtimecmph_clked = clint_mtimecmph;
    clint_mtime_clked = clint_mtime;
    clint_mtimeh_clked = clint_mtimeh;
    //not reg
    clint_mtip_clked = clint_mtip;

}