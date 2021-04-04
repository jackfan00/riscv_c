#include <stdio.h>
#include "ctradio.h"
#include "pwm.h"
#include "clint.h"
#include "dtcm.h"

void ctradio_clked()
{
    pwm2_cmp1ip_clked_d1 = pwm2_cmp1ip_clked;

    READY_eventip_clked = READY_eventip;
    END_eventip_clked = END_eventip;
    RADIO_TIMERCC_eventip_clked = RADIO_TIMERCC_eventip;


    //
    state_clked = state;

    reg_frequency_clked = reg_frequency;
    reg_accessaddr_clked = reg_accessaddr;
    reg_rampup_rxtime_clked = reg_rampup_rxtime;
    reg_rampup_txtime_clked = reg_rampup_txtime;
    reg_shorts_clked = reg_shorts;
    reg_short_READY_START = (reg_shorts_clked&short_READY_START)? 1 : 0;
    reg_short_END_DISABLE = (reg_shorts_clked&short_END_DISABLE)? 1 : 0;
    reg_short_CC_TXEN = (reg_shorts_clked&short_TIMERCC_TXEN)? 1 : 0;
    reg_short_CC_RXEN = (reg_shorts_clked&short_TIMERCC_RXEN)? 1 : 0;
    reg_short_END_CC = (reg_shorts_clked&short_END_TIMERCC)? 1 : 0;
    reg_short_pwm2cmp1_CC = (reg_shorts_clked&short_pwm2cmp1_TIMERCC)? 1 : 0;
    reg_timercc_clked = reg_timercc;
    reg_START_task_clked = reg_START_task;
    reg_DISABLE_task_clked = reg_DISABLE_task;
    reg_disabled_time_clked = reg_disabled_time;
    reg_TXEN_task_clked = reg_TXEN_task;
    reg_RXEN_task_clked = reg_RXEN_task;
    reg_pylen_clked = reg_pylen;
    reg_packetptr_clked = reg_packetptr;
    reg_bcc_clked = reg_bcc;
    reg_timercc_start_clked = reg_timercc_start;
    reg_timercc_stop_clked = reg_timercc_stop;

    TIMERCCper_clked = TIMERCCper;
    radioclk_cnt_clked = radioclk_cnt;
    TIMERCC_cnt_clked = TIMERCC_cnt;
    blebit_cnt_clked = blebit_cnt;
    bitper_clked = bitper;
    biten_cnt_clked = biten_cnt;
    blebit_cnt_en_clked = blebit_cnt_en;
    ramp_up_cnt_clked = ramp_up_cnt;
    disable_cnt_clked = disable_cnt;

    t1_cnt_clked =t1_cnt;
    t2_cnt_clked =t2_cnt;


    radio_read_clked = radio_read;
    radio_write_clked = radio_write;
    radio_read1st_clked = radio_read1st;
    read_radio_rdat_clked = read_radio_rdat;
    radio_csadr_clked = radio_regcs ? radio_regwadr : radio_csadr_clked;

//  for debug
//  print info                       

    if (START_task){
        printf("%d, Premable,accessaddr:%08x-freq:%d-",clockcnt, reg_accessaddr_clked, reg_frequency_clked);
    }
    if (tx_ADDRESS_event){
        printf("packet:");
    }
    if (packeten){
        if (bank==0)
            printf("%02x-",dtcmRAM0[byteadr>>2]);
        if (bank==1)
            printf("%02x-",dtcmRAM1[byteadr>>2]);
        if (bank==2)
            printf("%02x-",dtcmRAM2[byteadr>>2]);
        if (bank==3)
            printf("%02x-",dtcmRAM3[byteadr>>2]);
    }
    if (PAYLOAD_event){
        printf("crc24:");
    }
    if (END_event){
        printf("end\n");
    }
    byte_cnt_clked = !txper ? 0 :
                      ((txbit_cnt_clked==7)&(txhclk_cnt_clked==(HCLKMHZ-1))) ? byte_cnt_clked+1 : byte_cnt_clked;
    txbit_cnt_clked = (!txper)|((txbit_cnt_clked==7)&(txhclk_cnt_clked==(HCLKMHZ-1))) ? 0 :
                       (txhclk_cnt_clked==(HCLKMHZ-1)) ? txbit_cnt_clked+1 : txbit_cnt_clked;
    txhclk_cnt_clked = (!txper)|(txhclk_cnt_clked==(HCLKMHZ-1)) ? 0 :
                        txhclk_cnt_clked+1;

}