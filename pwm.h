#ifndef PWM_H
#define PWM_H
#include "reg.h"
void pwm();
void pwm_clked();

#define PWM0_BASE   0x10015000
#define PWM1_BASE   0x10025000
#define PWM2_BASE   0x10035000
#define PWM0_CMPWIDTH   8
#define PWM1_CMPWIDTH   16
#define PWM2_CMPWIDTH   16
#define PWM0_COUNTWIDTH 15+PWM0_CMPWIDTH
#define PWM1_COUNTWIDTH 15+PWM1_CMPWIDTH
#define PWM2_COUNTWIDTH 15+PWM2_CMPWIDTH

#define PWM2_CFG   PWM2_BASE+0x00
#define PWM2_COUNT PWM2_BASE+0x08
#define PWM2_S     PWM2_BASE+0x10
#define PWM2_CMP0  PWM2_BASE+0x20
#define PWM2_CMP1  PWM2_BASE+0x24
#define PWM2_CMP2  PWM2_BASE+0x28
#define PWM2_CMP3  PWM2_BASE+0x2C


//
BIT pwm_read_clked;
BIT pwm_write_clked;
BIT pwm_read1st_clked;
REG32 read_pwm_rdat_clked;
REG32 pwm_csadr_clked;

REG32 pwm2_cfg_clked;
REG32 pwm2_cmp0_clked;
REG32 pwm2_cmp1_clked;
REG32 pwm2_cmp2_clked;
REG32 pwm2_cmp3_clked;
REG32 pwm2_count_clked;
BIT pwm2_cmp0center;
BIT pwm2_cmp1center;
BIT pwm2_cmp2center;
BIT pwm2_cmp3center;
REG8 pwm2_scale;
BIT pwm2_zerocmp;
BIT pwm2_enalways;
BIT pwm2_oneshot;
BIT pwm2_deglitch;
BIT pwm2_stickyip;
BIT pwm2_cmp0gang;
BIT pwm2_cmp1gang;
BIT pwm2_cmp2gang;
BIT pwm2_cmp3gang;
BIT pwm2_cmp0ip_clked;
BIT pwm2_cmp1ip_clked;
BIT pwm2_cmp2ip_clked;
BIT pwm2_cmp3ip_clked;
BIT pwm2_sticky_deglich_clked;

//output
BIT pwm_regcs;
BIT pwm_regw;
REG32 pwm_regwdata;
REG32 pwm_regwadr;
REG32 pwm_regradr;
BIT pwm_cmd_valid;
BIT pwm_cmd_ready;
BIT pwm_cmd_read;
REG32 pwm_cmd_adr;
REG32 pwm_cmd_data;
BIT pwm_rsp_valid;
BIT pwm_rsp_ready;
BIT pwm_rsp_read;
REG32 pwm_rsp_rdata;
BIT pwm_read;
REG32 pwm_rdat;
BIT pwm_write;
BIT pwm_read1st;
REG32 read_pwm_rdat;

REG32 pwm2_cfg;
REG32 pwm2_cmp0;
REG32 pwm2_cmp1;
REG32 pwm2_cmp2;
REG32 pwm2_cmp3;
REG32 pwm2_count;
REG32 pwm2_s;
BIT pwm2_reset;

REG32 pwm2_s_cmp;
BIT pwm2_cmp0_res;
BIT pwm2_cmp1_res;
BIT pwm2_cmp2_res;
BIT pwm2_cmp3_res;
BIT pwm2_s_carry;
BIT pwm2_sticky_deglich;
BIT pwm2_cmp0ip_t;
BIT pwm2_cmp1ip_t;
BIT pwm2_cmp2ip_t;
BIT pwm2_cmp3ip_t;
BIT pwm2_cmp0ip;
BIT pwm2_cmp1ip;
BIT pwm2_cmp2ip;
BIT pwm2_cmp3ip;
BIT pwm2_cmp0gpio;
BIT pwm2_cmp1gpio;
BIT pwm2_cmp2gpio;
BIT pwm2_cmp3gpio;

#endif //PWM_H