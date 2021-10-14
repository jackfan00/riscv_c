#include <stdio.h>
#include "myradio.h"
#include "pwm.h"
#include "clint.h"
#include "dtcm.h"

void myradio_clked()
{

    END_event_clked = END_event;
    READY_event_clked = READY_event;
    ADDRESS_event_clked = ADDRESS_event;
    PAYLOAD_event_clked = PAYLOAD_event;
    DISABLED_event_clked = DISABLED_event;

    //READY_eventip_clked = READY_eventip;
    //END_eventip_clked = END_eventip;
    //ADDRESS_eventip_clked = ADDRESS_eventip;
    //DISABLED_eventip_clked = DISABLED_eventip;
    //RADIO_TIMERCC_eventip_clked = RADIO_TIMERCC_eventip;
    //
    radioss_state_clked = radioss_state;
    reg_frequency_clked = reg_frequency;
    reg_accessaddr_clked = reg_accessaddr;
    reg_rampup_rxtime_clked = reg_rampup_rxtime;
    reg_rampup_txtime_clked = reg_rampup_txtime;
    reg_shorts_clked = reg_shorts;
    reg_disabled_time_clked = reg_disabled_time;
    //reg_START_task_clked = reg_START_task;
    //reg_DISABLE_task_clked = reg_DISABLE_task;
    //reg_TXEN_task_clked = reg_TXEN_task;
    //reg_RXEN_task_clked = reg_RXEN_task;
    reg_pylen_clked = reg_pylen;
    reg_packetptr_clked = reg_packetptr;
    reg_bcc_clked = reg_bcc;
    reg_radioss_inten_clked = reg_radioss_inten;


    reg_timercc0_clked = reg_timercc0;
    reg_timercc1_clked = reg_timercc1;
    reg_timercc2_clked = reg_timercc2;
    reg_timercc3_clked = reg_timercc3;
    TIMER_compare0_event_clked = TIMER_compare0_event;
    TIMER_compare1_event_clked = TIMER_compare1_event;
    TIMER_compare2_event_clked = TIMER_compare2_event;
    TIMER_compare3_event_clked = TIMER_compare3_event;
    TIMER_cnt_clked = TIMER_cnt;
    TIMERper_clked = TIMERper;
    TIMER_START_task_per_clked = TIMER_START_task_per;
    TIMER_STOP_task_per_clked = TIMER_STOP_task_per;
    TIMER_CLEAR_task_per_clked = TIMER_CLEAR_task_per;



    radioss_cnt_clked = radioss_cnt;



    radio_read_clked = radio_read;
    radio_write_clked = radio_write;
    radio_read1st_clked = radio_read1st;
    read_radio_rdat_clked = read_radio_rdat;
    radio_csadr_clked = radio_regcs ? radio_regwadr : radio_csadr_clked;



}