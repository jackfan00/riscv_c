#include "pwm.h"

void pwm()
{
//    pwm_cmd_ready = (!pwm_rsp_read) | (pwm_rsp_read&pwm_rsp_ready);
    pwm_cmd_ready = (!pwm_rsp_valid) | (pwm_rsp_valid&pwm_rsp_ready);

    pwm_regcs = pwm_cmd_valid & pwm_cmd_ready;// ? 1 : 0;
    pwm_regw = !pwm_cmd_read;
    pwm_regwadr = pwm_cmd_adr;
    pwm_regwdata = pwm_cmd_data;
    //
    pwm2_cfg = pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CFG) ? (pwm_regwdata&0x0fffffff) : 
                pwm2_cfg_clked;

    pwm2_cmp0 = pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CMP0) ? pwm_regwdata : pwm2_cmp0_clked;
    pwm2_cmp1 = pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CMP1) ? pwm_regwdata : pwm2_cmp1_clked;
    pwm2_cmp2 = pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CMP2) ? pwm_regwdata : pwm2_cmp2_clked;
    pwm2_cmp3 = pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CMP3) ? pwm_regwdata : pwm2_cmp3_clked;

    pwm2_count = pwm2_reset ? 0 : 
                 pwm2_enalways|pwm2_oneshot ? pwm2_count_clked+1 : pwm2_count_clked;
    pwm2_s_cmp = pwm2_cmp0center & (pwm2_s>>15)  ? ~pwm2_s : pwm2_s; 
    pwm2_cmp0_res = (pwm2_s_cmp >= pwm2_cmp0_clked);
    pwm2_s_carry = ((1<<(pwm2_scale+PWM2_CMPWIDTH)-1)==pwm2_count_clked);
    pwm2_reset = (pwm2_cmp0_res & pwm2_zerocmp) | pwm2_s_carry | 
            (pwm2_count_clked== ((unsigned int)(1<<PWM2_COUNTWIDTH)-1) );
    pwm2_sticky_deglich = (pwm2_deglitch & (!pwm2_reset)) | pwm2_stickyip;

    pwm2_cmp0ip_t = pwm2_cmp0center & (pwm2_s>>15) ? pwm2_cmp0_res :
                    (pwm2_cmp0ip_clked & pwm2_sticky_deglich_clked) | pwm2_cmp0_res;
    pwm2_cmp0ip =  pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CFG) ? (pwm_regwdata>>28)&0x1 : pwm2_cmp0ip_t;
    pwm2_cmp0gpio =  pwm2_cmp0ip_clked & (!(pwm2_cmp0gang & pwm2_cmp1ip_clked));

    pwm2_cmp1_res = (pwm2_s_cmp >= pwm2_cmp1_clked);
    pwm2_cmp1ip_t = pwm2_cmp1center & (pwm2_s>>15) ? pwm2_cmp1_res :
                    (pwm2_cmp1ip_clked & pwm2_sticky_deglich_clked) | pwm2_cmp1_res;
    pwm2_cmp1ip =  pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CFG) ? (pwm_regwdata>>29)&0x1 : pwm2_cmp1ip_t;
    pwm2_cmp1gpio =  pwm2_cmp1ip_clked & (!(pwm2_cmp1gang & pwm2_cmp2ip_clked));

    pwm2_cmp2_res = (pwm2_s_cmp >= pwm2_cmp2_clked);
    pwm2_cmp2ip_t = pwm2_cmp2center & (pwm2_s>>15) ? pwm2_cmp2_res :
                    (pwm2_cmp2ip_clked & pwm2_sticky_deglich_clked) | pwm2_cmp2_res;
    pwm2_cmp2ip =  pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CFG) ? (pwm_regwdata>>30)&0x1 : pwm2_cmp2ip_t;
    pwm2_cmp2gpio =  pwm2_cmp2ip_clked & (!(pwm2_cmp2gang & pwm2_cmp3ip_clked));

    pwm2_cmp3_res = (pwm2_s_cmp >= pwm2_cmp3_clked);
    pwm2_cmp3ip_t = pwm2_cmp3center & (pwm2_s>>15) ? pwm2_cmp3_res :
                    (pwm2_cmp3ip_clked & pwm2_sticky_deglich_clked) | pwm2_cmp3_res;
    pwm2_cmp3ip =  pwm_regcs & pwm_regw & (pwm_regwadr==PWM2_CFG) ? (pwm_regwdata>>31)&0x1 : pwm2_cmp3ip_t;
    pwm2_cmp3gpio =  pwm2_cmp3ip_clked & (!(pwm2_cmp3gang & pwm2_cmp0ip_clked));

    //regrdata
    pwm_rdat = 
                (pwm_csadr_clked==PWM2_CFG) ? pwm2_cfg_clked|(pwm2_cmp3ip_clked<<31)|
                            (pwm2_cmp2ip_clked<<30)|(pwm2_cmp1ip_clked<<29)|(pwm2_cmp0ip_clked<<28) :
                (pwm_csadr_clked==PWM2_CMP0) ? pwm2_cmp0_clked :
                (pwm_csadr_clked==PWM2_CMP1) ? pwm2_cmp1_clked :
                (pwm_csadr_clked==PWM2_CMP2) ? pwm2_cmp2_clked :
                (pwm_csadr_clked==PWM2_CMP3) ? pwm2_cmp3_clked :
                (pwm_csadr_clked==PWM2_COUNT) ? pwm2_count_clked :
                (pwm_csadr_clked==PWM2_S) ? pwm2_s : 
                 0;

    pwm_read =    pwm_regcs & (!pwm_regw) ? 1 : 
                    pwm_read_clked&pwm_rsp_ready ? 0 :
                    //pwm_rsp_valid & pwm_rsp_ready & (pwm_cmd_valid ? pwm_cmd_read:1)? 0 :
                    pwm_read_clked;

    pwm_write = pwm_regcs  & (pwm_regw) ? 1: 
                       pwm_write_clked& pwm_rsp_ready ? 0 :
                       pwm_write_clked;
    

    pwm_rsp_valid = 
                            pwm_read_clked | pwm_write_clked ? 1 : 0;
                        //pwm_regcs & pwm_regw? 1 : //combinational loop issue
                        //pwm_read_clked;
    pwm_read1st = pwm_regcs & (!pwm_regw) ? 1: 0;
    read_pwm_rdat = pwm_read1st_clked ? pwm_rdat : read_pwm_rdat_clked;

    pwm_rsp_rdata =  (pwm_read1st_clked ? pwm_rdat : read_pwm_rdat_clked)  ;

    pwm_rsp_read =  pwm_read_clked;    
}