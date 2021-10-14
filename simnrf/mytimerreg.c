#include <stdio.h>
#include "myradio.h"
#include "myscvr.h"

void mytimerreg_setup()
{
    REG64 regbase;
    NRF_TIMER_Type timerst;
    regbase = &timerst + NRF_TIMER0_BASE;
    TIMER_INTENSET_ADDR = &(timerst.INTENSET) - regbase;
    TIMER_INTENCLR_ADDR = &(timerst.INTENCLR) - regbase;
    TIMER_START_ADDR = &(timerst.TASKS_START) - regbase;
    TIMER_STOP_ADDR = &(timerst.TASKS_STOP) - regbase;
    TIMER_CLEAR_ADDR = &(timerst.TASKS_CLEAR) - regbase;
    TIMER_CC0_ADDR = &(timerst.CC[0]) - regbase;
    TIMER_CC1_ADDR = &(timerst.CC[1]) - regbase;
    TIMER_CC2_ADDR = &(timerst.CC[2]) - regbase;
    TIMER_CC3_ADDR = &(timerst.CC[3]) - regbase;
    TIMER_EVENTS_COMPARE0_ADDR = &(timerst.EVENTS_COMPARE[0]) - regbase;
    TIMER_EVENTS_COMPARE1_ADDR = &(timerst.EVENTS_COMPARE[1]) - regbase;
    TIMER_EVENTS_COMPARE2_ADDR = &(timerst.EVENTS_COMPARE[2]) - regbase;
    TIMER_EVENTS_COMPARE3_ADDR = &(timerst.EVENTS_COMPARE[3]) - regbase;
    TIMER_TASK_CAPTURE0_ADDR = &(timerst.TASKS_CAPTURE[0]) - regbase;
    TIMER_TASK_CAPTURE1_ADDR = &(timerst.TASKS_CAPTURE[1]) - regbase;
    TIMER_TASK_CAPTURE2_ADDR = &(timerst.TASKS_CAPTURE[2]) - regbase;
    TIMER_TASK_CAPTURE3_ADDR = &(timerst.TASKS_CAPTURE[3]) - regbase;
    //


}

void mytimerreg()
{
    BIT END_eventip_p;
    BIT ADDRESS_eventip_p;
    BIT DISABLED_eventip_p;
    REG32 timer_intenset;
    REG32 timer_intenclr;


    //radio interrupt pending
    TIMER_compare0_event    = radio_regcs & radio_regw & (radio_regwadr==TIMER_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : TIMER_compare0_event_p    | TIMER_compare0_event_clked;
    TIMER_compare0_eventip = TIMER_compare0_event_clked & ((reg_timer_inten_clked & TIMER_INTENCLR_COMPARE0_Msk)!=0);
    TIMER_compare1_event    = radio_regcs & radio_regw & (radio_regwadr==TIMER_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : TIMER_compare1_event_p    | TIMER_compare1_event_clked;
    TIMER_compare1_eventip = TIMER_compare1_event_clked & ((reg_timer_inten_clked & TIMER_INTENCLR_COMPARE1_Msk)!=0);
    TIMER_compare2_event    = radio_regcs & radio_regw & (radio_regwadr==TIMER_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : TIMER_compare2_event_p    | TIMER_compare2_event_clked;
    TIMER_compare2_eventip = TIMER_compare2_event_clked & ((reg_timer_inten_clked & TIMER_INTENCLR_COMPARE2_Msk)!=0);
    TIMER_compare3_event    = radio_regcs & radio_regw & (radio_regwadr==TIMER_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : TIMER_compare3_event_p    | TIMER_compare3_event_clked;
    TIMER_compare3_eventip = TIMER_compare3_event_clked & ((reg_timer_inten_clked & TIMER_INTENCLR_COMPARE3_Msk)!=0);
    timer_ip = TIMER_compare0_eventip | TIMER_compare1_eventip | TIMER_compare2_eventip | TIMER_compare3_eventip;
//

    //interrupt reg
    timer_intenset = radio_regcs & radio_regw & (radio_regwadr==TIMER_INTENSET_ADDR) ? radio_regwdata : 0;
    timer_intenclr = radio_regcs & radio_regw & (radio_regwadr==TIMER_INTENCLR_ADDR) ? radio_regwdata : 0;
    reg_timer_inten = (reg_timer_inten_clked | timer_intenset) | 
            (reg_timer_inten_clked & (~timer_intenclr));

    reg_TIMER_START_task_p         = radio_regcs & radio_regw & (radio_regwadr==TIMER_START_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TIMER_STOP_task_p          = radio_regcs & radio_regw & (radio_regwadr==TIMER_STOP_ADDR)  ? radio_regwdata&0x01 : 0;
    reg_TIMER_CLEAR_task_p         = radio_regcs & radio_regw & (radio_regwadr==TIMER_CLEAR_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TIMER_capture0_task_p      = radio_regcs & radio_regw & (radio_regwadr==TIMER_TASK_CAPTURE0_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TIMER_capture1_task_p      = radio_regcs & radio_regw & (radio_regwadr==TIMER_TASK_CAPTURE1_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TIMER_capture2_task_p      = radio_regcs & radio_regw & (radio_regwadr==TIMER_TASK_CAPTURE2_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TIMER_capture3_task_p      = radio_regcs & radio_regw & (radio_regwadr==TIMER_TASK_CAPTURE3_ADDR) ? radio_regwdata&0x01 : 0;

    //regrdata
    timer_rdat = 
                (radio_csadr_clked==TIMER_INTENSET_ADDR) ? reg_timer_inten_clked :
                (radio_csadr_clked==TIMER_INTENCLR_ADDR) ? reg_timer_inten_clked :
                (radio_csadr_clked==TIMER_EVENTS_COMPARE0_ADDR) ? TIMER_compare0_event_clked : 
                (radio_csadr_clked==TIMER_EVENTS_COMPARE1_ADDR) ? TIMER_compare1_event_clked : 
                (radio_csadr_clked==TIMER_EVENTS_COMPARE2_ADDR) ? TIMER_compare2_event_clked : 
                (radio_csadr_clked==TIMER_EVENTS_COMPARE3_ADDR) ? TIMER_compare3_event_clked : 
                (radio_csadr_clked==TIMER_CC0_ADDR) ? reg_timercc0_clked : 
                (radio_csadr_clked==TIMER_CC1_ADDR) ? reg_timercc1_clked : 
                (radio_csadr_clked==TIMER_CC2_ADDR) ? reg_timercc2_clked : 
                (radio_csadr_clked==TIMER_CC3_ADDR) ? reg_timercc3_clked : 
                (radio_csadr_clked==TIMER_IP_ADDR) ? timer_ip : 
                 0;




}