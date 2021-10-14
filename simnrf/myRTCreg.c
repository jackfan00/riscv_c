#include <stdio.h>
#include "myradio.h"
#include "myscvr.h"

void myRTCreg_setup()
{
    REG64 regbase;
    NRF_RTC_Type timerst;
    regbase = &timerst + NRF_RTC0_BASE;
    RTC_INTENSET_ADDR = &(timerst.INTENSET) - regbase;
    RTC_INTENCLR_ADDR = &(timerst.INTENCLR) - regbase;
    RTC_START_ADDR = &(timerst.TASKS_START) - regbase;
    RTC_STOP_ADDR = &(timerst.TASKS_STOP) - regbase;
    RTC_CLEAR_ADDR = &(timerst.TASKS_CLEAR) - regbase;
    RTC_CC0_ADDR = &(timerst.CC[0]) - regbase;
    RTC_CC1_ADDR = &(timerst.CC[1]) - regbase;
    RTC_CC2_ADDR = &(timerst.CC[2]) - regbase;
    RTC_CC3_ADDR = &(timerst.CC[3]) - regbase;
    RTC_EVENTS_COMPARE0_ADDR = &(timerst.EVENTS_COMPARE[0]) - regbase;
    RTC_EVENTS_COMPARE1_ADDR = &(timerst.EVENTS_COMPARE[1]) - regbase;
    RTC_EVENTS_COMPARE2_ADDR = &(timerst.EVENTS_COMPARE[2]) - regbase;
    RTC_EVENTS_COMPARE3_ADDR = &(timerst.EVENTS_COMPARE[3]) - regbase;
    //RTC_TASK_CAPTURE0_ADDR = &(timerst.TASKS_CAPTURE[0]) - regbase;
    //RTC_TASK_CAPTURE1_ADDR = &(timerst.TASKS_CAPTURE[1]) - regbase;
    //RTC_TASK_CAPTURE2_ADDR = &(timerst.TASKS_CAPTURE[2]) - regbase;
    //RTC_TASK_CAPTURE3_ADDR = &(timerst.TASKS_CAPTURE[3]) - regbase;
    //


}

void myRTCreg()
{
    BIT END_eventip_p;
    BIT ADDRESS_eventip_p;
    BIT DISABLED_eventip_p;
    REG32 RTC_intenset;
    REG32 RTC_intenclr;


    //radio interrupt pending
    RTC_compare0_event    = radio_regcs & radio_regw & (radio_regwadr==RTC_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : RTC_compare0_event_p    | RTC_compare0_event_clked;
    RTC_compare0_eventip = RTC_compare0_event_clked & ((reg_RTC_inten_clked & RTC_INTENCLR_COMPARE0_Msk)!=0);
    RTC_compare1_event    = radio_regcs & radio_regw & (radio_regwadr==RTC_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : RTC_compare1_event_p    | RTC_compare1_event_clked;
    RTC_compare1_eventip = RTC_compare1_event_clked & ((reg_RTC_inten_clked & RTC_INTENCLR_COMPARE1_Msk)!=0);
    RTC_compare2_event    = radio_regcs & radio_regw & (radio_regwadr==RTC_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : RTC_compare2_event_p    | RTC_compare2_event_clked;
    RTC_compare2_eventip = RTC_compare2_event_clked & ((reg_RTC_inten_clked & RTC_INTENCLR_COMPARE2_Msk)!=0);
    RTC_compare3_event    = radio_regcs & radio_regw & (radio_regwadr==RTC_EVENTS_COMPARE0_ADDR)    ? radio_regwdata&0x01 : RTC_compare3_event_p    | RTC_compare3_event_clked;
    RTC_compare3_eventip = RTC_compare3_event_clked & ((reg_RTC_inten_clked & RTC_INTENCLR_COMPARE3_Msk)!=0);
    RTC_ip = RTC_compare0_eventip | RTC_compare1_eventip | RTC_compare2_eventip | RTC_compare3_eventip;
//

    //interrupt reg
    RTC_intenset = radio_regcs & radio_regw & (radio_regwadr==RTC_INTENSET_ADDR) ? radio_regwdata : 0;
    RTC_intenclr = radio_regcs & radio_regw & (radio_regwadr==RTC_INTENCLR_ADDR) ? radio_regwdata : 0;
    reg_RTC_inten = (reg_RTC_inten_clked | RTC_intenset) | 
            (reg_RTC_inten_clked & (~RTC_intenclr));

    reg_RTC_START_task_p         = radio_regcs & radio_regw & (radio_regwadr==RTC_START_ADDR) ? radio_regwdata&0x01 : 0;
    reg_RTC_STOP_task_p          = radio_regcs & radio_regw & (radio_regwadr==RTC_STOP_ADDR)  ? radio_regwdata&0x01 : 0;
    reg_RTC_CLEAR_task_p         = radio_regcs & radio_regw & (radio_regwadr==RTC_CLEAR_ADDR) ? radio_regwdata&0x01 : 0;
    //reg_RTC_capture0_task_p      = radio_regcs & radio_regw & (radio_regwadr==RTC_TASK_CAPTURE0_ADDR) ? radio_regwdata&0x01 : 0;
    //reg_RTC_capture1_task_p      = radio_regcs & radio_regw & (radio_regwadr==RTC_TASK_CAPTURE1_ADDR) ? radio_regwdata&0x01 : 0;
    //reg_RTC_capture2_task_p      = radio_regcs & radio_regw & (radio_regwadr==RTC_TASK_CAPTURE2_ADDR) ? radio_regwdata&0x01 : 0;
    //reg_RTC_capture3_task_p      = radio_regcs & radio_regw & (radio_regwadr==RTC_TASK_CAPTURE3_ADDR) ? radio_regwdata&0x01 : 0;

    //regrdata
    RTC_rdat = 
                (radio_csadr_clked==RTC_INTENSET_ADDR) ? reg_RTC_inten_clked :
                (radio_csadr_clked==RTC_INTENCLR_ADDR) ? reg_RTC_inten_clked :
                (radio_csadr_clked==RTC_EVENTS_COMPARE0_ADDR) ? RTC_compare0_event_clked : 
                (radio_csadr_clked==RTC_EVENTS_COMPARE1_ADDR) ? RTC_compare1_event_clked : 
                (radio_csadr_clked==RTC_EVENTS_COMPARE2_ADDR) ? RTC_compare2_event_clked : 
                (radio_csadr_clked==RTC_EVENTS_COMPARE3_ADDR) ? RTC_compare3_event_clked : 
                (radio_csadr_clked==RTC_CC0_ADDR) ? reg_RTCcc0_clked : 
                (radio_csadr_clked==RTC_CC1_ADDR) ? reg_RTCcc1_clked : 
                (radio_csadr_clked==RTC_CC2_ADDR) ? reg_RTCcc2_clked : 
                (radio_csadr_clked==RTC_CC3_ADDR) ? reg_RTCcc3_clked : 
                (radio_csadr_clked==RTC_IP_ADDR) ? RTC_ip : 
                 0;




}