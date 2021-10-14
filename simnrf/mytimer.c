#include <stdio.h>
#include "myradio.h"



void mytimer()
{
    //sync with us_p
    TIMER_START_task_per = TIMER_START_task_p ? 1 : 
                            us_p ? 0 : TIMER_START_task_per_clked;
    TIMER_STOP_task_per = TIMER_STOP_task_p ? 1 : 
                            us_p ? 0 : TIMER_STOP_task_per_clked;
    TIMER_CLEAR_task_per = TIMER_CLEAR_task_p ? 1 : 
                            us_p ? 0 : TIMER_CLEAR_task_per_clked;

    //
    TIMERper = TIMER_START_task_per_clked & us_p ? 1 :
            TIMER_STOP_task_per_clked & us_p ? 0 : TIMERper_clked;
    TIMER_cnt = !TIMERper_clked ? TIMER_cnt_clked :
                TIMER_CLEAR_task_per_clked & us_p ? 0 : 
                TIMER_cnt_clked +1;
    //
    TIMER_compare0_event_p = (reg_timercc0_clked==TIMER_cnt_clked) & TIMERper_clked;
    TIMER_compare1_event_p = (reg_timercc1_clked==TIMER_cnt_clked) & TIMERper_clked;
    TIMER_compare2_event_p = (reg_timercc2_clked==TIMER_cnt_clked) & TIMERper_clked;
    TIMER_compare3_event_p = (reg_timercc3_clked==TIMER_cnt_clked) & TIMERper_clked;
    //TIMER_compare_event4_p = (reg_timercc4_clked==TIMER_cnt_clked) & TIMERper_clked;


 

    reg_timercc0 = radio_regcs & radio_regw & (radio_regwadr==TIMER_CC0_ADDR) ? radio_regwdata : 
                    TIMER_capture0_task_p ? TIMER_cnt_clked : reg_timercc0_clked;
    reg_timercc1 = radio_regcs & radio_regw & (radio_regwadr==TIMER_CC1_ADDR) ? radio_regwdata : 
                    TIMER_capture1_task_p ? TIMER_cnt_clked : reg_timercc1_clked;
    reg_timercc2 = radio_regcs & radio_regw & (radio_regwadr==TIMER_CC2_ADDR) ? radio_regwdata : 
                    TIMER_capture2_task_p ? TIMER_cnt_clked : reg_timercc2_clked;
    reg_timercc3 = radio_regcs & radio_regw & (radio_regwadr==TIMER_CC3_ADDR) ? radio_regwdata : 
                    TIMER_capture3_task_p ? TIMER_cnt_clked : reg_timercc3_clked;
//    reg_timercc4 = radio_regcs & radio_regw & (radio_regwadr==TIMER_CC4_ADDR) ? radio_regwdata : 
//                    TIMER_capture_task4 ? TIMER_cnt_clked : reg_timercc4_clked;



}