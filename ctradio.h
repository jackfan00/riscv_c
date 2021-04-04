#ifndef CTRADIO_H
#define CTRADIO_H

#include "reg.h"
void ctradio();
void ctradio_clked();

#define DISABLED 0
#define TXRU 1
#define RXRU 2
#define TXIDLE 3
#define RXIDLE 4
#define TX 5
#define RX 6
#define TXDISABLE 7
#define RXDISABLE 8
//reg
#define CT_RADIO_BASE              0x10401000UL
#define RADIO_FREQUENCY_ADDR               CT_RADIO_BASE+26*4 
#define RADIO_ACCESS_ADDR               CT_RADIO_BASE+25*4 
#define RADIO_TASK_TIMERCC_STOP_ADDR     CT_RADIO_BASE+24*4 
#define RADIO_TASK_TIMERCC_START_ADDR     CT_RADIO_BASE+23*4 
#define RADIO_DISABLED_TIME_ADDR    CT_RADIO_BASE+22*4 
#define RADIO_RAMPUP_RXTIME_ADDR    CT_RADIO_BASE+21*4 
#define RADIO_RAMPUP_TXTIME_ADDR    CT_RADIO_BASE+20*4 
#define RADIO_IP_ADDR               CT_RADIO_BASE+19*4 
#define RADIO_TIMERCC_ADDR          CT_RADIO_BASE+18*4 
#define RADIO_BCC_ADDR              CT_RADIO_BASE+17*4 
#define RADIO_STATE_ADDR            CT_RADIO_BASE+16*4 
#define RADIO_PYLEN_ADDR            CT_RADIO_BASE+15*4 
#define RADIO_PACKETPTR_ADDR        CT_RADIO_BASE+14*4 
#define RADIO_SHORTS_ADDR           CT_RADIO_BASE+13*4 
#define RADIO_DISABLE_ADDR          CT_RADIO_BASE+4*4 
#define RADIO_START_ADDR            CT_RADIO_BASE+2*4 
#define RADIO_RXEN_ADDR             CT_RADIO_BASE+1*4 
#define RADIO_TXEN_ADDR             CT_RADIO_BASE+0*4 

#define END_eventip_Msk                0x01
#define RADIO_TIMERCC_eventip_Msk           0x02
#define READY_eventip_Msk              0x04

#define short_TIMERCC_TXEN              0x01
#define short_TIMERCC_RXEN              0x02
#define short_END_TIMERCC               0x04
#define short_pwm2cmp1_TIMERCC          0x08
#define short_READY_START          0x10
#define short_END_DISABLE          0x20

BIT pwm2_cmp1ip_clked_d1;

REG8 state;
REG8 state_clked;
BIT TXEN_task;
BIT RXEN_task;
BIT START_task;
BIT READY_event;
BIT DISABLE_task;
BIT END_event;
BIT STOP_task;
BIT DISABLED_event;
BIT BCSTART_task;
BIT BCSTOP_task;
BIT PAYLOAD_event;
BIT ADDRESS_event;
BIT tx_ADDRESS_event;
BIT rx_ADDRESS_event;
BIT BCMATCH_event;
BIT READY_eventip;
BIT READY_eventip_clked;
BIT END_eventip;
BIT END_eventip_clked;
BIT RADIO_TIMERCC_eventip;
BIT RADIO_TIMERCC_eventip_clked;
BIT RADIO_TIMERCC_event;
BIT radio_ip;

BIT bitper;
BIT bitper_clked;
REG16 blebit_cnt;
REG16 blebit_cnt_clked;
REG8 biten_cnt;
REG8 biten_cnt_clked;
BIT biten_p;
BIT blebit_cnt_en;
BIT blebit_cnt_en_clked;
REG16 ramp_up_cnt;
REG16 ramp_up_cnt_clked;
BIT ramp_up_per;
BIT disable_per;
REG16 disable_cnt;
REG16 disable_cnt_clked;
BIT RADIO_TIMERCC_start;
BIT RADIO_TIMERCC_stop;
REG16 TIMERCC_cnt;
REG16 TIMERCC_cnt_clked;
BIT TIMERCCper;
BIT TIMERCCper_clked;
BIT us_p;
REG8 radioclk_cnt;
REG8 radioclk_cnt_clked;
REG16 t1_cnt;
REG16 t1_cnt_clked;
REG16 t2_cnt;
REG16 t2_cnt_clked;
BIT r_us_p;
BIT d_us_p;

REG32 reg_frequency;
REG32 reg_frequency_clked;
REG32 reg_accessaddr;
REG32 reg_accessaddr_clked;
REG32 reg_packetptr;
REG32 reg_packetptr_clked;
REG32 reg_disabled_time;
REG32 reg_disabled_time_clked;
REG32 reg_rampup_txtime;
REG32 reg_rampup_txtime_clked;
REG32 reg_rampup_rxtime;
REG32 reg_rampup_rxtime_clked;
REG32 reg_shorts;
REG32 reg_shorts_clked;
BIT reg_short_READY_START;
BIT reg_short_END_DISABLE;
BIT reg_short_CC_TXEN;
BIT reg_short_CC_RXEN;
BIT reg_short_END_CC;
BIT reg_short_pwm2cmp1_CC;
REG32 reg_timercc;
REG32 reg_timercc_clked;
BIT reg_START_task;
BIT reg_START_task_clked;
BIT reg_DISABLE_task;
BIT reg_DISABLE_task_clked;
BIT reg_TXEN_task;
BIT reg_TXEN_task_clked;
BIT reg_RXEN_task;
BIT reg_RXEN_task_clked;
REG32 reg_pylen;
REG32 reg_pylen_clked;
REG32 reg_bcc;
REG32 reg_bcc_clked;
BIT reg_timercc_start;
BIT reg_timercc_start_clked;
BIT reg_timercc_stop;
BIT reg_timercc_stop_clked;

BIT radio_regcs;
BIT radio_regw;
REG32 radio_regwadr;
REG32 radio_regwdata;
BIT radio_cmd_valid;
BIT radio_cmd_ready;
BIT radio_cmd_read;
REG32 radio_cmd_adr;
REG32 radio_cmd_data;
BIT radio_read;
BIT radio_read_clked;
BIT radio_write;
BIT radio_write_clked;
BIT radio_rsp_valid;
BIT radio_rsp_ready;
REG32 radio_rsp_rdata;
REG32 radio_csadr_clked;
REG32 radio_rdat;
BIT radio_read1st;
BIT radio_read1st_clked;
REG32 read_radio_rdat;
REG32 read_radio_rdat_clked;
BIT radio_rsp_read;


//for debug
BIT txper;
REG8 txhclk_cnt;
REG8 txhclk_cnt_clked;
REG8 txbit_cnt;
REG8 txbit_cnt_clked;
REG16 byte_cnt;
REG16 byte_cnt_clked;
BIT byte_endp;
REG32 byteadr;
REG8 bank;
BIT packeten;

#endif //CTRADIO_H