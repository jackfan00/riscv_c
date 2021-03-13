#include "plic.h"
#include "execu.h"
#include "gpio.h"
#include "uart.h"
#include "pwm.h"

void plicunit(BIT intsource, BIT loIP_clked, BIT gateway_enable, REG8 priority, BIT loIE, REG8 ID, REG8 prepriorityout,  REG8 premaxid,
BIT *IP, REG8 *priorityout, REG8 *maxid
)

{

    REG8 ippriority;
    REG8 iepriproty;
    BIT ishighpriority;

    //gateway: translate intsource (which is from interrupt pending register) to once intreq
    //         and masked next intsource until intreq is processed completely.

    //interrupt pending register from 0 -> 1
    //if (!(intsource_clked) & intsource)
    //{
    //    *IP = gateway_enable;
    //}
    //else{
    //    *IP =0;
    //}

    // intsource 1 means interrupt
    *IP = gateway_enable & intsource;
    ippriority = (loIP_clked) ? priority : 0 ; 
    //
    iepriproty = loIE ? ippriority : 0;
    ishighpriority = (iepriproty > prepriorityout);
    *priorityout = ishighpriority ? ippriority : prepriorityout;
    *maxid = ishighpriority ? ID : premaxid;

    //if (loIE>0 && priority>0 && loIP_clked>0){
    //    printf("%d-%d-%d\n",loIE, ippriority, ID);
    //}

}

void plic()
{
    int i;
    REG8 IE_idx;
    REG8 prepriorityout[PLIC_INTNUMBER];
    REG8 premaxid[PLIC_INTNUMBER];

    //plic intsource connection : same as SiFive
    for (i=0;i<32;i++){
        intsource[8+i] = (gpio_intr_clked>>i) & 0x01;
    }
    //uart
    intsource[3] = uart_intr_clked;
    //pwm2
    intsource[48] = pwm2_cmp0ip_clked;
    intsource[49] = pwm2_cmp1ip_clked;
    intsource[50] = pwm2_cmp2ip_clked;
    intsource[51] = pwm2_cmp3ip_clked;


    
    //plic function block
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        prepriorityout[i] = (i==1) ? 0 : priorityout[i-1];
        premaxid[i] = (i==1) ? 0 : maxid[i-1];
        //
        IE_idx = (i>>5);
        dbgie[i] = (IE_clked[IE_idx]>>(i&0x1f))&0x01;
        plicunit(intsource[i], (IP_clked[IE_idx]>>(i&0x1f))&0x01, gateway_enable_clked[i], priority_clked[i], (IE_clked[IE_idx]>>(i&0x1f))&0x01 , i, prepriorityout[i],  premaxid[i],
        &IP[i], &priorityout[i], &maxid[i]);
        //
    }

    EIP = (priorityout[PLIC_INTNUMBER-1]>prioritythreshold_clked);
    INTID = maxid[PLIC_INTNUMBER-1];

    //plic bus read/write
    //plic_cmd_ready = plic_cmd_valid & (!plic_rsp_valid | (plic_rsp_valid & plic_rsp_ready));
    //plic_cmd_ready = plic_cmd_valid & plic_rsp_ready;
    //plic_cmd_ready = (!plic_rsp_read) | (plic_rsp_read&plic_rsp_ready);
    plic_cmd_ready = (!plic_rsp_valid) | (plic_rsp_valid&plic_rsp_ready);


    plic_regcs = plic_cmd_valid & plic_cmd_ready;// ? 1 : 0;
    plic_regw =  !plic_cmd_read ;
    plic_regwdata =  plic_cmd_data ;
    plic_regwadr =  plic_cmd_adr ;
    //plic_regradr = plic_regcs & (!plic_regw) ? plic_cmd_adr : plic_csadr_clked;
    //claim/complete pulse
    ccw = plic_regcs & plic_regw & (plic_regwadr==(PLIC_CLAIMCOMPLETE)) ;
    //ccr = plic_regcs & !plic_regw & (plic_regwadr==(PLIC_CLAIMCOMPLETE)) ;
    ccr = (plic_csadr_clked==(PLIC_CLAIMCOMPLETE)) & (plic_rsp_read&plic_rsp_ready);

    //regrdata
    plic_rdat=0;
    for (i=1;i<PLIC_INTNUMBER;i++)
    {
        plic_rdat = plic_rdat | ((plic_csadr_clked==(PLIC_PRIORITY_BASE+i*4)) ? priority_clked[i]:0);
    }

    for (i=0;i<(PLIC_INTNUMBER>>5);i++)
    {
        plic_rdat = plic_rdat | ((plic_csadr_clked==(PLIC_IE_BASE+i*4))       ? IE_clked[i]:0      );
        plic_rdat = plic_rdat | ((plic_csadr_clked==(PLIC_IP_BASE+i*4))       ? IP_clked[i] : 0    );
    }
        plic_rdat = plic_rdat | ((plic_csadr_clked==(PLIC_CLAIMCOMPLETE))     ? INTID_clked : 0    );
        plic_rdat = plic_rdat | ((plic_csadr_clked==(PLIC_PRI_THRESHOLD))     ? prioritythreshold_clked : 0    );
    //
    plic_read =     plic_regcs     & (!plic_regw) ? 1 : 
                    plic_read_clked&plic_rsp_ready ? 0 :
                    //plic_rsp_valid &   plic_rsp_ready & (plic_cmd_valid ? plic_cmd_read:1) ? 0 : //eliminate write case
                    plic_read_clked;
    //plic_write = plic_regcs  & (plic_regw) ? 1: 0;
    plic_write = plic_regcs  & (plic_regw) ? 1: 
                       plic_write_clked& plic_rsp_ready ? 0 :
                       plic_write_clked;

    plic_rsp_valid = //plic_regcs & plic_regw? 1 :  //combinational loop issue
                            plic_read_clked | plic_write_clked ? 1 : 0;
                     //   plic_read_clked;

    plic_read1st = plic_regcs & (!plic_regw) ? 1: 0;
    read_plic_rdat = plic_read1st_clked ? plic_rdat : read_plic_rdat_clked;

    plic_rsp_rdata =  (plic_read1st_clked ? plic_rdat : read_plic_rdat_clked)  ;

    plic_rsp_read = plic_read_clked;

    //plic_rsp_rdata = plic_rdat;

}