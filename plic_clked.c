#include "plic.h"

void plic_clked()
{
    int i;

    //
    EIP_clked = EIP;
    INTID_clked = INTID;


    //plic registers
    //priority 0:reserved, 1- 1023
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        priority_clked[i] = plic_regcs & plic_regw & (plic_regwadr==(PLIC_PRIORITY_BASE+i*4)) ? plic_regwdata : priority_clked[i];
    }

    //IP regsiter, read-only 
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        IP_clked[i>>5] = IP_clked[i>>5] | ((IP[i])<<i);
    }

    IP_clked[plic_rsp_rdata>>5] = ccr ? IP_clked[plic_rsp_rdata>>5] & (~(1<<plic_rsp_rdata)) : IP_clked[plic_rsp_rdata>>5];

    //IE register
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        IE_clked[i] = plic_regcs & plic_regw & (plic_regwadr==(PLIC_IE_BASE+i*4)) ? plic_regwdata : IE_clked[i];
    }

    //target priority threshold
    prioritythreshold_clked = plic_regcs & plic_regw & (plic_regwadr==(PLIC_PRI_THRESHOLD)) ? plic_regwdata : priority_clked[i];

    //gateway control
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        gateway_enable_clked[i] = IP[i] ? 0 : gateway_enable_clked[i];
    }
    gateway_enable_clked[plic_regwdata] = ccw ? 1 : gateway_enable_clked[plic_regwdata];


    plic_read_clked = plic_read;

    plic_write_clked = plic_write;
    plic_read1st_clked = plic_read1st;
    read_plic_rdat_clked = read_plic_rdat;
    plic_csadr_clked = plic_regcs ? plic_regwadr : plic_csadr_clked;

}