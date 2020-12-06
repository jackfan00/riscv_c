#include "csrreg.h"

void csrreg_clked()
{
    mtval_clked = mtval;
    mscratch_clked = mscratch;
    mtvec_clked = mtvec;
    mcause_clked = mcause;
    mepc_clked = mepc;
    mstatusmie_clked = mstatusmie;
    mstatusmpie_clked = mstatusmpie;
    mie_clked = mie;
    mcycle_clked = mcycle;
    mcycleh_clked = mcycleh;
    minstret_clked = minstret;
    minstreth_clked = minstreth;

}