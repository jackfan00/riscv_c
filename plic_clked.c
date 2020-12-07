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

    IP_clked[plic_regwdata] = ccr ? IP_clked[plic_regwdata>>5] & (~(1<<plic_regwdata)) : IP_clked[plic_regwdata];

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
        gateway_enable_clked[i] = IP[i] ? 1 : gateway_enable_clked[i];
    }
    gateway_enable_clked[plic_regwdata] = ccw ? 1 : gateway_enable_clked[plic_regwdata];


}