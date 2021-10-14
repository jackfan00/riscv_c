#include <stdio.h>
#include "myradio.h"



void myRTC()
{
    //sync with clk32768_p
    RTC_START_task_per = RTC_START_task_p ? 1 : 
                            clk32768_p ? 0 : RTC_START_task_per_clked;
    RTC_STOP_task_per = RTC_STOP_task_p ? 1 : 
                            clk32768_p ? 0 : RTC_STOP_task_per_clked;
    RTC_CLEAR_task_per = RTC_CLEAR_task_p ? 1 : 
                            clk32768_p ? 0 : RTC_CLEAR_task_per_clked;

    //
    RTCper = RTC_START_task_per_clked & clk32768_p ? 1 :
            RTC_STOP_task_per_clked & clk32768_p ? 0 : RTCper_clked;
    RTC_cnt = !RTCper_clked ? RTC_cnt_clked :
                RTC_CLEAR_task_per_clked & clk32768_p ? 0 : 
                RTC_cnt_clked +1;
    //
    RTC_compare0_event_p = (reg_RTCcc0_clked==RTC_cnt_clked) & RTCper_clked;
    RTC_compare1_event_p = (reg_RTCcc1_clked==RTC_cnt_clked) & RTCper_clked;
    RTC_compare2_event_p = (reg_RTCcc2_clked==RTC_cnt_clked) & RTCper_clked;
    RTC_compare3_event_p = (reg_RTCcc3_clked==RTC_cnt_clked) & RTCper_clked;
    //RTC_compare_event4_p = (reg_RTCcc4_clked==RTC_cnt_clked) & RTCper_clked;


 

    reg_RTCcc0 = radio_regcs & radio_regw & (radio_regwadr==RTC_CC0_ADDR) ? radio_regwdata : 
                    RTC_capture0_task_p ? RTC_cnt_clked : reg_RTCcc0_clked;
    reg_RTCcc1 = radio_regcs & radio_regw & (radio_regwadr==RTC_CC1_ADDR) ? radio_regwdata : 
                    RTC_capture1_task_p ? RTC_cnt_clked : reg_RTCcc1_clked;
    reg_RTCcc2 = radio_regcs & radio_regw & (radio_regwadr==RTC_CC2_ADDR) ? radio_regwdata : 
                    RTC_capture2_task_p ? RTC_cnt_clked : reg_RTCcc2_clked;
    reg_RTCcc3 = radio_regcs & radio_regw & (radio_regwadr==RTC_CC3_ADDR) ? radio_regwdata : 
                    RTC_capture3_task_p ? RTC_cnt_clked : reg_RTCcc3_clked;
//    reg_RTCcc4 = radio_regcs & radio_regw & (radio_regwadr==RTC_CC4_ADDR) ? radio_regwdata : 
//                    RTC_capture_task4 ? RTC_cnt_clked : reg_RTCcc4_clked;



}