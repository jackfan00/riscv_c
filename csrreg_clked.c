#include <stdio.h>
#include "csrreg.h"
#include "plic.h"

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

    csr_inthappen_st_p_clked =  csr_cmd_exception_ready ? 0 :  //1st priority
                                csr_inthappen_st_p ? 1 :
                                csr_inthappen_st_p_clked;

    //if (csr_inthappen_st_p & EIP_clked & (clockcnt >=5300147)){
    //    printf("csrint:%d, mcause:0x%x\n", clockcnt, mcause);
    //}
}