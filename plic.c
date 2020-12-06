#include "plic.h"
#include "execu.h"

void plicunit(BIT intsource, BIT intsource_clked, BIT gateway_enable, REG8 priority, BIT IE, REG8 ID, REG8 prepriorityout,  REG8 premaxid,
BIT *IP, REG8 *priorityout, REG8 *maxid
)

{

    REG8 ippriority;
    REG8 iepriproty;
    BIT ishighpriority;

    //gateway: translate intsource (which is from interrupt pending register) to once intreq
    //         and masked next intsource until intreq is processed completely.

    //interrupt pending register from 0 -> 1
    if (!(intsource_clked) & intsource)
    {
        *IP = gateway_enable;
    }
    else{
        *IP =0;
    }
    ippriority = (*IP) ? priority : 0 ; 
    //
    iepriproty = IE ? ippriority : 0;
    ishighpriority = (iepriproty > prepriorityout);
    *priorityout = ishighpriority ? ippriority : prepriorityout;
    *maxid = ishighpriority ? ID : premaxid;
}

void plic()
{
    int i;
    REG8 prepriorityout[PLIC_INTNUMBER];
    REG8 premaxid[PLIC_INTNUMBER];
    
    //plic function block
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        prepriorityout[i] = (i==1) ? 0 : *priorityout[i-1];
        premaxid[i] = (i==1) ? 0 : *maxid[i-1];
        //
        plicunit(intsource[i], intsource_clked[i], gateway_enable_clked[i], priority_clked[i], IE_clked[i], i, prepriorityout[i],  premaxid[i],
        *IP[i], *priorityout[i], *maxid[i]);
        //
    }

    EIP = (*priorityout[PLIC_INTNUMBER-1]>prioritythreshold_clked);
    INTID = *maxid[PLIC_INTNUMBER-1];

    //plic bus read/write
    plic_cmd_ready = plic_cmd_valid & 1;
    plic_regcs = plic_cmd_valid & plic_cmd_ready ? 1 : 0;
    plic_regw = plic_cmd_valid & plic_cmd_ready ? !plic_cmd_read : 0;
    plic_regwdata = plic_cmd_valid & plic_cmd_ready ? plic_cmd_data : 0;
    plic_regadr = plic_cmd_valid & plic_cmd_ready ? plic_cmd_adr : 0;

    //regrdata
    plic_regrdata=0;
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        plic_regrdata = plic_regrdata | (plic_regcs & !plic_regw & (plic_regadr==(PLIC_PRIORITY_BASE+i*4)) ? priority_clked[i]:0);
        plic_regrdata = plic_regrdata | (plic_regcs & !plic_regw & (plic_regadr==(PLIC_IE_BASE+i*4)) ? IE_clked[i]:0);
    }

    for (i=0;i<(PLIC_INTNUMBER>>5);i++)
    {
        plic_regrdata = plic_regrdata | (plic_regcs & !plic_regw & (plic_regadr==(PLIC_IP_BASE+i*4)) ? IP_clked[i] : 0);
    }
    plic_regrdata = plic_regrdata | (ccr ? INTID_clked : 0);
    //
    plic_rsp_valid = plic_regcs ;
    plic_rsp_rdata = plic_regrdata;

}