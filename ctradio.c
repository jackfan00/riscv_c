#include <stdio.h>
#include "ctradio.h"
#include "clint.h"
#include "pwm.h"

void ctradio()
{
    REG32 ramp_up_time;
    BIT READY_eventip_t;
    BIT END_eventip_t;
    BIT RADIO_TIMERCC_eventip_t;
    BIT pwm2_cmp1ip_p;
    REG16 Plen;
    REG16 Alen;
    REG16 S0len;
    REG16 Llen;
    REG16 S1len;
    REG16 PAYLOADlen;
    REG16 CRClen;
    // event/task is 1 clk pulse
    state = state_clked;
    switch(state_clked)
    {
        case DISABLED:
                if (TXEN_task)
                    state = TXRU;
                else if (RXEN_task)
                    state = RXRU;    
                break;    
        case TXRU:
                if (READY_event & START_task)
                    state = TX;
                else if (READY_event)
                    state = TXIDLE;
                else if (DISABLE_task)
                    state = TXDISABLE;    
                break;    
        case RXRU:
                if (READY_event & START_task)
                    state = RX;
                else if (READY_event)
                    state = RXIDLE;
                else if (DISABLE_task)
                    state = RXDISABLE;    
                break;    
        case TXIDLE:
                if (START_task)
                    state = TX;
                else if (DISABLE_task)  
                    state = TXDISABLE;
                break;    
        case RXIDLE:
                if (START_task)
                    state = RX;
                else if (DISABLE_task)  
                    state = RXDISABLE;
                break;    
        case TX:
                if (END_event & DISABLE_task)
                    state = TXDISABLE;
                else if (END_event)
                    state = TXIDLE;
                else if (STOP_task)
                    state = TXIDLE;    
                else if (DISABLE_task)
                    state = TXDISABLE;    
                break;    
        case RX:
                if (END_event & DISABLE_task)
                    state = RXDISABLE;
                else if (END_event)
                    state = RXIDLE;
                else if (STOP_task)
                    state = RXIDLE;    
                else if (DISABLE_task)
                    state = RXDISABLE;    
                break;    
        case TXDISABLE:
                if (DISABLED_event)
                    state = DISABLED;
                break;    
        case RXDISABLE:
                if (DISABLED_event)
                    state = DISABLED;
                break;    
        default:  //error state
                printf("ERR::wrong ctradio state=%d\n", state_clked);
                break;
    }
    //ramp-up time
    t1_cnt =  !ramp_up_per ? 0 : 
                    r_us_p ? 0 : t1_cnt_clked+1;
    r_us_p = (t1_cnt_clked==(HCLKMHZ-1));

    ramp_up_per = (state_clked==TXRU)|(state_clked==RXRU);
    ramp_up_cnt =   !ramp_up_per ? 0 : 
                    READY_event ? 0 :
                    r_us_p ? ramp_up_cnt_clked+1 : ramp_up_cnt_clked;
    ramp_up_time = (state_clked==TXRU) ? reg_rampup_txtime_clked : reg_rampup_rxtime_clked;

    READY_event = (ramp_up_cnt_clked==ramp_up_time) & ramp_up_per & r_us_p;
    READY_eventip_t = READY_event ? 1 : READY_eventip_clked | READY_event;
    READY_eventip = radio_regcs & radio_regw & (radio_regwadr==RADIO_IP_ADDR) & ((radio_regwdata&READY_eventip_Msk)!=0) ? 0 : READY_eventip_t;

    START_task = reg_short_READY_START ? READY_event : reg_START_task_clked;

    DISABLE_task = reg_short_END_DISABLE ? END_event : reg_DISABLE_task_clked;

    //disabled time
    t2_cnt =  !disable_per ? 0 : 
                    d_us_p ? 0 : t2_cnt_clked+1;
    d_us_p = (t2_cnt_clked==(HCLKMHZ-1));

    disable_per = (state_clked==TXDISABLE)|(state_clked==RXDISABLE);
    disable_cnt =   !disable_per ? 0 : 
                    DISABLED_event ? 0 :
                    d_us_p ? disable_cnt_clked+1 : disable_cnt_clked;
    DISABLED_event = (disable_cnt_clked==reg_disabled_time_clked) & disable_per & d_us_p;

    //PPI automatically start TXEN/RXEN
    TXEN_task = reg_short_CC_TXEN ? RADIO_TIMERCC_event : reg_TXEN_task_clked;
    RXEN_task = 
                reg_short_CC_RXEN ? RADIO_TIMERCC_event : reg_RXEN_task_clked;

    //bit counter
    bitper =    START_task | BCSTART_task ? 1 :
                STOP_task|BCSTOP_task|END_event|DISABLE_task ? 0 : bitper_clked;
    blebit_cnt =    !bitper_clked ? 0 :
                    START_task | BCSTART_task | ADDRESS_event ? 0 :
                    bitper_clked & biten_p ? blebit_cnt_clked + 1 : 
                    blebit_cnt_clked;
    biten_cnt =     !bitper_clked ? 0 :
                    START_task | BCSTART_task ? 0 :
                    biten_p ? 0 :
                    bitper_clked ? biten_cnt_clked + 1 : 
                    biten_cnt_clked;
    biten_p = (biten_cnt_clked==(HCLKMHZ-1));
    blebit_cnt_en = ADDRESS_event ? 1 : 
                    END_event|DISABLE_task ? 0 :
                    blebit_cnt_en_clked;


    //bits
    Plen=8;
    Alen=32;
    S0len=8;
    Llen=8;
    S1len=8;
    CRClen=24;
    PAYLOADlen=(reg_pylen_clked<<3);
    tx_ADDRESS_event = (!blebit_cnt_en_clked) & biten_p & (blebit_cnt_clked==(((Plen+Alen))-1));    
    rx_ADDRESS_event = 0;  
    ADDRESS_event = state_clked == TX ? tx_ADDRESS_event : rx_ADDRESS_event;
    //   
    PAYLOAD_event = blebit_cnt_en_clked & biten_p & (blebit_cnt_clked==(((S0len+Llen+S1len+PAYLOADlen))-1));         
    END_event     = blebit_cnt_en_clked & biten_p & (blebit_cnt_clked==(((S0len+Llen+S1len+PAYLOADlen+CRClen))-1));         
    BCMATCH_event = biten_p & (blebit_cnt_clked==((reg_bcc_clked<<3)-1));

    //radio interrupt, write 1 clear
    END_eventip_t =  END_event ? 1 : END_eventip_clked | END_event;
    END_eventip = radio_regcs & radio_regw & (radio_regwadr==RADIO_IP_ADDR) & ((radio_regwdata&END_eventip_Msk)!=0) ? 0 : END_eventip_t;

    //rising-edge to 1 pulse
    pwm2_cmp1ip_p = (pwm2_cmp1ip_clked==1) & (pwm2_cmp1ip_clked_d1==0);
    //oneshot radio timer, us 
    RADIO_TIMERCC_start = reg_short_END_CC ? END_event : 
                    reg_short_pwm2cmp1_CC ? pwm2_cmp1ip_p : 
                    reg_timercc_start_clked;

    RADIO_TIMERCC_event = (reg_timercc_clked==TIMERCC_cnt_clked) & TIMERCCper_clked;

    RADIO_TIMERCC_eventip_t = RADIO_TIMERCC_event ? 1 : RADIO_TIMERCC_eventip_clked | RADIO_TIMERCC_event;
    RADIO_TIMERCC_eventip = radio_regcs & radio_regw & (radio_regwadr==RADIO_IP_ADDR) & ((radio_regwdata&RADIO_TIMERCC_eventip_Msk)!=0) ? 0 : RADIO_TIMERCC_eventip_t;

    TIMERCC_cnt =    !TIMERCCper_clked ? 0 :
                TIMERCCper_clked & us_p ? TIMERCC_cnt_clked + 1 : 
                TIMERCC_cnt_clked;
    radioclk_cnt =  !TIMERCCper_clked ? 0 : 
                    us_p ? 0 : radioclk_cnt_clked+1;

    us_p = (radioclk_cnt_clked==(HCLKMHZ-1));

    TIMERCCper = RADIO_TIMERCC_start ? 1 :
            RADIO_TIMERCC_event| RADIO_TIMERCC_stop ? 0 : TIMERCCper_clked;

    radio_ip = END_eventip_clked|RADIO_TIMERCC_eventip_clked;//|READY_eventip_clked;


//
    radio_cmd_ready = (!radio_rsp_valid) | (radio_rsp_valid&radio_rsp_ready);

    radio_regcs = radio_cmd_valid & radio_cmd_ready;// ? 1 : 0;
    radio_regw = !radio_cmd_read;
    radio_regwadr = radio_cmd_adr;
    radio_regwdata = radio_cmd_data;


    reg_frequency = radio_regcs & radio_regw & (radio_regwadr==RADIO_FREQUENCY_ADDR) ? radio_regwdata : reg_frequency_clked;
    reg_accessaddr = radio_regcs & radio_regw & (radio_regwadr==RADIO_ACCESS_ADDR) ? radio_regwdata : reg_accessaddr_clked;
    reg_rampup_txtime = radio_regcs & radio_regw & (radio_regwadr==RADIO_RAMPUP_TXTIME_ADDR) ? radio_regwdata : reg_rampup_txtime_clked;
    reg_rampup_rxtime = radio_regcs & radio_regw & (radio_regwadr==RADIO_RAMPUP_RXTIME_ADDR) ? radio_regwdata : reg_rampup_rxtime_clked;
    reg_shorts = radio_regcs & radio_regw & (radio_regwadr==RADIO_SHORTS_ADDR) ? radio_regwdata : reg_shorts_clked;
    reg_timercc = radio_regcs & radio_regw & (radio_regwadr==RADIO_TIMERCC_ADDR) ? radio_regwdata : reg_timercc_clked;
    reg_START_task = radio_regcs & radio_regw & (radio_regwadr==RADIO_START_ADDR) ? radio_regwdata&0x01 : 
                    0 ;
    reg_DISABLE_task = radio_regcs & radio_regw & (radio_regwadr==RADIO_DISABLE_ADDR) ? radio_regwdata&0x01 : 
                    0 ;
    reg_TXEN_task = radio_regcs & radio_regw & (radio_regwadr==RADIO_TXEN_ADDR) ? radio_regwdata&0x01 : 
                    0 ;
    reg_RXEN_task = radio_regcs & radio_regw & (radio_regwadr==RADIO_RXEN_ADDR) ? radio_regwdata&0x01 : 
                    0 ;
    reg_disabled_time = radio_regcs & radio_regw & (radio_regwadr==RADIO_DISABLED_TIME_ADDR) ? radio_regwdata : reg_disabled_time_clked;
    reg_pylen = radio_regcs & radio_regw & (radio_regwadr==RADIO_PYLEN_ADDR) ? radio_regwdata : reg_pylen_clked;
    reg_packetptr = radio_regcs & radio_regw & (radio_regwadr==RADIO_PACKETPTR_ADDR) ? radio_regwdata : reg_packetptr_clked;
    reg_bcc = radio_regcs & radio_regw & (radio_regwadr==RADIO_BCC_ADDR) ? radio_regwdata : reg_bcc_clked;

    reg_timercc_start = radio_regcs & radio_regw & (radio_regwadr==RADIO_TASK_TIMERCC_START_ADDR) ? radio_regwdata&0x01 : 
                    0 ;
    reg_timercc_stop = radio_regcs & radio_regw & (radio_regwadr==RADIO_TASK_TIMERCC_STOP_ADDR) ? radio_regwdata&0x01 : 
                    0 ;

    //regrdata
    radio_rdat = 
                (radio_csadr_clked==RADIO_FREQUENCY_ADDR) ? reg_frequency_clked :
                (radio_csadr_clked==RADIO_RAMPUP_TXTIME_ADDR) ? reg_rampup_txtime_clked :
                (radio_csadr_clked==RADIO_RAMPUP_RXTIME_ADDR) ? reg_rampup_rxtime_clked :
                (radio_csadr_clked==RADIO_SHORTS_ADDR) ? reg_shorts_clked :
                (radio_csadr_clked==RADIO_TIMERCC_ADDR) ? reg_timercc_clked :
                (radio_csadr_clked==RADIO_DISABLED_TIME_ADDR) ? reg_disabled_time_clked :
                (radio_csadr_clked==RADIO_PYLEN_ADDR) ? reg_pylen_clked :
                (radio_csadr_clked==RADIO_BCC_ADDR) ? reg_bcc_clked :
                (radio_csadr_clked==RADIO_STATE_ADDR) ? state_clked : 
                (radio_csadr_clked==RADIO_IP_ADDR) ? radio_ip : 
                (radio_csadr_clked==RADIO_ACCESS_ADDR) ? reg_accessaddr : 
                 0;

    radio_read =    radio_regcs & (!radio_regw) ? 1 : 
                    radio_read_clked&radio_rsp_ready ? 0 :
                    //radio_rsp_valid & radio_rsp_ready & (radio_cmd_valid ? radio_cmd_read:1)? 0 :
                    radio_read_clked;

    radio_write = radio_regcs  & (radio_regw) ? 1: 
                       radio_write_clked& radio_rsp_ready ? 0 :
                       radio_write_clked;
    

    radio_rsp_valid = 
                            radio_read_clked | radio_write_clked ? 1 : 0;
                        //radio_regcs & radio_regw? 1 : //combinational loop issue
                        //radio_read_clked;
    radio_read1st = radio_regcs & (!radio_regw) ? 1: 0;
    read_radio_rdat = radio_read1st_clked ? radio_rdat : read_radio_rdat_clked;

    radio_rsp_rdata =  (radio_read1st_clked ? radio_rdat : read_radio_rdat_clked)  ;

    radio_rsp_read =  radio_read_clked;    


//for debug
    byteadr = (reg_packetptr_clked+byte_cnt_clked-5) & 0x00ffffff;
    bank = byteadr & 0x03;
    byte_endp = ((txbit_cnt_clked==7)&(txhclk_cnt_clked==(HCLKMHZ-1)));
    txper = (state_clked==TX);
    packeten = txper & byte_endp & blebit_cnt_en_clked;
}