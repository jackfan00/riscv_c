#include <stdio.h>
#include "pwm.h"


void pwm_clked()
{
    pwm_read_clked = pwm_read;
    pwm_write_clked = pwm_write;
    pwm_read1st_clked = pwm_read1st;
    read_pwm_rdat_clked = read_pwm_rdat;
    pwm_csadr_clked = pwm_regcs ? pwm_regwadr : pwm_csadr_clked;

    pwm2_cmp0ip_clked = pwm2_cmp0ip;
    pwm2_cmp1ip_clked = pwm2_cmp1ip;
    pwm2_cmp2ip_clked = pwm2_cmp2ip;
    pwm2_cmp3ip_clked = pwm2_cmp3ip;
    pwm2_cfg_clked = pwm2_cfg;
    pwm2_cmp0_clked  = pwm2_cmp0;
    pwm2_cmp1_clked  = pwm2_cmp1;
    pwm2_cmp2_clked  = pwm2_cmp2;
    pwm2_cmp3_clked  = pwm2_cmp3;
    pwm2_count_clked = pwm2_count;
//
    pwm2_scale = pwm2_cfg_clked & 0xf;
    pwm2_stickyip = (pwm2_cfg_clked>>8) & 0x1;
    pwm2_zerocmp = (pwm2_cfg_clked>>9) & 0x1;
    pwm2_deglitch = (pwm2_cfg_clked>>10) & 0x1;
    pwm2_enalways = (pwm2_cfg_clked>>12) & 0x1;
    pwm2_oneshot = (pwm2_cfg_clked>>13) & 0x1;
    pwm2_cmp0center = (pwm2_cfg_clked>>16) & 0x1;
    pwm2_cmp1center = (pwm2_cfg_clked>>17) & 0x1;
    pwm2_cmp2center = (pwm2_cfg_clked>>18) & 0x1;
    pwm2_cmp3center = (pwm2_cfg_clked>>19) & 0x1;
    pwm2_cmp0gang = (pwm2_cfg_clked>>24) & 0x1;
    pwm2_cmp1gang = (pwm2_cfg_clked>>25) & 0x1;
    pwm2_cmp2gang = (pwm2_cfg_clked>>26) & 0x1;
    pwm2_cmp3gang = (pwm2_cfg_clked>>27) & 0x1;


    pwm2_count_clked = pwm2_count;
    pwm2_s = (pwm2_count_clked >> pwm2_scale) & 0xffff;      



    //debug
    if (pwm_regcs  & pwm_regw){
        printf("write pwmreg %x, %x, pwms=%x, clockcnt=%d\n",pwm_regwadr, pwm_regwdata, pwm2_s, clockcnt);
    }

}