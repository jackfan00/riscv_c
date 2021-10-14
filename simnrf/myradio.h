#ifndef CTRADIO_H
#define CTRADIO_H

#include "../reg.h"
#include "../lowclkgen.h"

BIT usg(BIT inp);

void mytimer();
void myradio();
void myradioreg();
void myradio_clked();

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
//#define CT_RADIO_BASE              0x10401000UL
REG32  RADIO_FREQUENCY_ADDR          ; 
REG32  RADIO_ACCESS_ADDR             ; 
REG32  RADIO_TASK_TIMERCC_STOP_ADDR  ; 
REG32  RADIO_TASK_TIMERCC_START_ADDR ;  
REG32  RADIO_DISABLED_TIME_ADDR      ; 
REG32  RADIO_RAMPUP_RXTIME_ADDR      ; 
REG32  RADIO_RAMPUP_TXTIME_ADDR      ; 
REG32  RADIO_IP_ADDR                 ; 
REG32  TIMER_CC_ADDR            ; 
REG32  RADIO_BCC_ADDR                ; 
REG32  RADIO_STATE_ADDR              ; 
REG32  RADIO_PYLEN_ADDR              ; 
REG32  RADIO_PACKETPTR_ADDR          ; 
REG32  RADIO_SHORTS_ADDR             ; 
REG32  RADIO_DISABLE_ADDR            ; 
REG32  RADIO_STOP_ADDR               ; 
REG32  RADIO_START_ADDR              ; 
REG32  RADIO_RXEN_ADDR               ; 
REG32  RADIO_TXEN_ADDR               ;  
REG32  RADIO_INTENSET_ADDR           ;
REG32  RADIO_INTENCLR_ADDR           ;
REG32  RADIO_EVENTS_READY_ADDR       ;
REG32  RADIO_EVENTS_END_ADDR         ;
REG32  RADIO_EVENTS_ADDRESS_ADDR     ;
REG32  RADIO_EVENTS_PAYLOAD_ADDR     ;
REG32  RADIO_EVENTS_DISABLED_ADDR    ;
REG32  PPI_CHENSET_ADDR ;
REG32  PPI_CHENCLR_ADDR ;
REG32  PPI_CHEN_ADDR ;

REG32  TIMER_TASK_CAPTURE0_ADDR      ;
REG32  TIMER_TASK_CAPTURE1_ADDR      ;
REG32  TIMER_TASK_CAPTURE2_ADDR      ;
REG32  TIMER_TASK_CAPTURE3_ADDR      ;
REG32  TIMER_EVENTS_COMPARE0_ADDR       ;
REG32  TIMER_EVENTS_COMPARE1_ADDR         ;
REG32  TIMER_EVENTS_COMPARE2_ADDR     ;
REG32  TIMER_EVENTS_COMPARE3_ADDR     ;
REG32  TIMER_STOP_ADDR               ; 
REG32  TIMER_CLEAR_ADDR               ; 
REG32  TIMER_START_ADDR              ; 
REG32  TIMER_INTENSET_ADDR           ;
REG32  TIMER_INTENCLR_ADDR           ;
REG32  TIMER_CC0_ADDR           ;
REG32  TIMER_CC1_ADDR           ;
REG32  TIMER_CC2_ADDR           ;
REG32  TIMER_CC3_ADDR           ;
REG32  TIMER_IP_ADDR            ;



REG32  RTC_TASK_CAPTURE0_ADDR      ;
REG32  RTC_TASK_CAPTURE1_ADDR      ;
REG32  RTC_TASK_CAPTURE2_ADDR      ;
REG32  RTC_TASK_CAPTURE3_ADDR      ;
REG32  RTC_EVENTS_COMPARE0_ADDR       ;
REG32  RTC_EVENTS_COMPARE1_ADDR         ;
REG32  RTC_EVENTS_COMPARE2_ADDR     ;
REG32  RTC_EVENTS_COMPARE3_ADDR     ;
REG32  RTC_STOP_ADDR               ; 
REG32  RTC_CLEAR_ADDR               ; 
REG32  RTC_START_ADDR              ; 
REG32  RTC_INTENSET_ADDR           ;
REG32  RTC_INTENCLR_ADDR           ;
REG32  RTC_CC0_ADDR           ;
REG32  RTC_CC1_ADDR           ;
REG32  RTC_CC2_ADDR           ;
REG32  RTC_CC3_ADDR           ;
REG32  RTC_IP_ADDR            ;


BIT ADDRESS_eventip;
BIT ADDRESS_eventip_clked;
BIT READY_eventip;
BIT READY_eventip_clked;
BIT END_eventip;
BIT END_eventip_clked;
BIT DISABLED_eventip;
BIT DISABLED_eventip_clked;
BIT PAYLOAD_eventip;
REG8 radioss_state;
REG8 radioss_state_clked;
REG32 reg_radioss_inten;
REG32 reg_radioss_inten_clked;
BIT READY_event;
BIT READY_event_clked;
BIT END_event;
BIT END_event_clked;
BIT ADDRESS_event;
BIT ADDRESS_event_clked;
BIT PAYLOAD_event;
BIT PAYLOAD_event_clked;
BIT DISABLED_event;
BIT DISABLED_event_clked;

BIT ppi_TXEN_task_p;
BIT ppi_RXEN_task_p;
BIT TXEN_task_p;
BIT RXEN_task_p;
BIT sh_START_task_p;
BIT ppi_START_task_p;
BIT START_task_p;
BIT READY_event_p;
BIT sh_DISABLE_task_p;
BIT ppi_DISABLE_task_p;
BIT DISABLE_task_p;
BIT END_event_p;
BIT STOP_task_p;
BIT DISABLED_event_p;
BIT BCSTART_task_p;
BIT BCSTOP_task_p;
BIT PAYLOAD_event_p;
BIT ADDRESS_event_p;
BIT tx_ADDRESS_event_p;
BIT rx_ADDRESS_event_p;
BIT BCMATCH_event_p;
BIT radioss_ip;
REG32 radioss_cnt;
REG32 radioss_cnt_clked;
BIT bitper;
BIT bitper_clked;
BIT ramp_up_per;
BIT disable_per;

BIT TIMER_compare0_event_p;
BIT TIMER_compare1_event_p;
BIT TIMER_compare2_event_p;
BIT TIMER_compare3_event_p;
BIT TIMER_compare0_event;
BIT TIMER_compare0_event_clked;
BIT TIMER_compare1_event;
BIT TIMER_compare1_event_clked;
BIT TIMER_compare2_event;
BIT TIMER_compare2_event_clked;
BIT TIMER_compare3_event;
BIT TIMER_compare3_event_clked;
BIT TIMER_compare0_eventip;
BIT TIMER_compare1_eventip;
BIT TIMER_compare2_eventip;
BIT TIMER_compare3_eventip;
BIT ppi_TIMER_capture1_task_p;
BIT ppi_TIMER_capture2_task_p;
BIT ppi_TIMER_capture3_task_p;
BIT reg_TIMER_capture0_task_p;
BIT reg_TIMER_capture1_task_p;
BIT reg_TIMER_capture2_task_p;
BIT reg_TIMER_capture3_task_p;
BIT TIMER_capture0_task_p;
BIT TIMER_capture1_task_p;
BIT TIMER_capture2_task_p;
BIT TIMER_capture3_task_p;
BIT TIMER_START_task_per;
BIT TIMER_START_task_per_clked;
BIT TIMER_STOP_task_per;
BIT TIMER_STOP_task_per_clked;
BIT TIMER_CLEAR_task_per;
BIT TIMER_CLEAR_task_per_clked;

REG32 reg_timercc0;
REG32 reg_timercc0_clked;
REG32 reg_timercc1;
REG32 reg_timercc1_clked;
REG32 reg_timercc2;
REG32 reg_timercc2_clked;
REG32 reg_timercc3;
REG32 reg_timercc3_clked;
BIT reg_TIMER_START_task_p;
BIT reg_TIMER_STOP_task_p;
BIT reg_TIMER_CLEAR_task_p;
BIT TIMER_START_task_p;
BIT TIMER_STOP_task_p;
BIT TIMER_CLEAR_task_p;
REG32 reg_timer_inten;
REG32 reg_timer_inten_clked;
BIT timer_ip;
REG16 TIMER_cnt;
REG16 TIMER_cnt_clked;
BIT TIMERper;
BIT TIMERper_clked;
REG32 timer_rdat;



BIT RTC_compare0_event_p;
BIT RTC_compare1_event_p;
BIT RTC_compare2_event_p;
BIT RTC_compare3_event_p;
BIT RTC_compare0_event;
BIT RTC_compare0_event_clked;
BIT RTC_compare1_event;
BIT RTC_compare1_event_clked;
BIT RTC_compare2_event;
BIT RTC_compare2_event_clked;
BIT RTC_compare3_event;
BIT RTC_compare3_event_clked;
BIT RTC_compare0_eventip;
BIT RTC_compare1_eventip;
BIT RTC_compare2_eventip;
BIT RTC_compare3_eventip;
BIT ppi_RTC_capture1_task_p;
BIT ppi_RTC_capture2_task_p;
BIT ppi_RTC_capture3_task_p;
BIT reg_RTC_capture0_task_p;
BIT reg_RTC_capture1_task_p;
BIT reg_RTC_capture2_task_p;
BIT reg_RTC_capture3_task_p;
BIT RTC_capture0_task_p;
BIT RTC_capture1_task_p;
BIT RTC_capture2_task_p;
BIT RTC_capture3_task_p;
BIT RTC_START_task_per;
BIT RTC_START_task_per_clked;
BIT RTC_STOP_task_per;
BIT RTC_STOP_task_per_clked;
BIT RTC_CLEAR_task_per;
BIT RTC_CLEAR_task_per_clked;

REG32 reg_RTCcc0;
REG32 reg_RTCcc0_clked;
REG32 reg_RTCcc1;
REG32 reg_RTCcc1_clked;
REG32 reg_RTCcc2;
REG32 reg_RTCcc2_clked;
REG32 reg_RTCcc3;
REG32 reg_RTCcc3_clked;
BIT reg_RTC_START_task_p;
BIT reg_RTC_STOP_task_p;
BIT reg_RTC_CLEAR_task_p;
BIT RTC_START_task_p;
BIT RTC_STOP_task_p;
BIT RTC_CLEAR_task_p;
REG32 reg_RTC_inten;
REG32 reg_RTC_inten_clked;
BIT RTC_ip;
REG16 RTC_cnt;
REG16 RTC_cnt_clked;
BIT RTCper;
BIT RTCper_clked;
REG32 RTC_rdat;


REG8 radioclk_cnt;
REG8 radioclk_cnt_clked;

REG32 reg_chen_clked;
REG32 reg_chen;
REG32 reg_chenset;
REG32 reg_chenclr;
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


BIT reg_START_task_p;
BIT reg_STOP_task_p;
BIT reg_DISABLE_task_p;
BIT reg_TXEN_task_p;
BIT reg_RXEN_task_p;

BIT reg_RXEN_task_p_clked;
BIT reg_TXEN_task_p_clked;
BIT reg_DISABLE_task_p_clked;
BIT reg_STOP_task_p_clked;
BIT reg_START_task_p_clked;
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