#include <stdio.h>
#include "myradio.h"
#include "myscvr.h"


void myradio()
{
    REG32 ramp_up_time;
    BIT READY_event_pip_t;
    BIT END_event_pip_t;
    BIT RADIO_TIMERCC_event_pip_t;
    BIT pwm2_cmp1ip_p;
    REG16 Plen;
    REG16 Alen;
    REG16 S0len;
    REG16 Llen;
    REG16 S1len;
    REG16 PAYLOADlen;
    REG16 CRClen;
    // event/task is 1 clk pulse
    radioss_state = radioss_state_clked;
    switch(radioss_state_clked)
    {
        case DISABLED:
                if (TXEN_task_p)
                    radioss_state = TXRU;
                else if (RXEN_task_p)
                    radioss_state = RXRU;    
                break;    
        case TXRU:
                if (READY_event_p & START_task_p)
                    radioss_state = TX;
                else if (READY_event_p)
                    radioss_state = TXIDLE;
                else if (DISABLE_task_p)
                    radioss_state = TXDISABLE;    
                break;    
        case RXRU:
                if (READY_event_p & START_task_p)
                    radioss_state = RX;
                else if (READY_event_p)
                    radioss_state = RXIDLE;
                else if (DISABLE_task_p)
                    radioss_state = RXDISABLE;    
                break;    
        case TXIDLE:
                if (START_task_p)
                    radioss_state = TX;
                else if (DISABLE_task_p)  
                    radioss_state = TXDISABLE;
                break;    
        case RXIDLE:
                if (START_task_p)
                    radioss_state = RX;
                else if (DISABLE_task_p)  
                    radioss_state = RXDISABLE;
                break;    
        case TX:
                if (END_event_p & DISABLE_task_p)
                    radioss_state = TXDISABLE;
                else if (END_event_p)
                    radioss_state = TXIDLE;
                else if (STOP_task_p)
                    radioss_state = TXIDLE;    
                else if (DISABLE_task_p)
                    radioss_state = TXDISABLE;    
                break;    
        case RX:
                if (END_event_p & DISABLE_task_p)
                    radioss_state = RXDISABLE;
                else if (END_event_p)
                    radioss_state = RXIDLE;
                else if (STOP_task_p)
                    radioss_state = RXIDLE;    
                else if (DISABLE_task_p)
                    radioss_state = RXDISABLE;    
                break;    
        case TXDISABLE:
                if (DISABLED_event_p)
                    radioss_state = DISABLED;
                break;    
        case RXDISABLE:
                if (DISABLED_event_p)
                    radioss_state = DISABLED;
                break;    
        default:  //error radioss_state
                printf("ERR::wrong myradio radioss_state=%d\n", radioss_state_clked);
                break;
    }
    //bits
    Plen=8;
    Alen=32;
    S0len=8;
    Llen=8;
    S1len=8;
    CRClen=24;
    PAYLOADlen=(reg_pylen_clked<<3);

    radioss_cnt = (radioss_state_clked==DISABLED) ? 0 :
                    TXEN_task_p|RXEN_task_p|READY_event_p|START_task_p|END_event_p ? 0 :
                    us_p ? radioss_cnt_clked+1 : radioss_cnt_clked;
    //ramp-up time
    ramp_up_per = (radioss_state_clked==TXRU)|(radioss_state_clked==RXRU);
    ramp_up_time = (radioss_state_clked==TXRU) ? reg_rampup_txtime_clked : reg_rampup_rxtime_clked;
    READY_event_p = (radioss_cnt_clked==ramp_up_time) & ramp_up_per & us_p;

    //bit period
    bitper = (radioss_state_clked==TX)|(radioss_state_clked==RX);
    tx_ADDRESS_event_p = bitper & (radioss_cnt_clked==(((Plen+Alen))-1));    
    ADDRESS_event_p = radioss_state_clked == TX ? tx_ADDRESS_event_p : rx_ADDRESS_event_p;
    PAYLOAD_event_p = bitper & (radioss_cnt_clked==(((S0len+Llen+S1len+PAYLOADlen))-1));         
    END_event_p     = bitper & (radioss_cnt_clked==(((S0len+Llen+S1len+PAYLOADlen+CRClen))-1));         

    //disabled time
    disable_per = (radioss_state_clked==TXDISABLE)|(radioss_state_clked==RXDISABLE);
    DISABLED_event_p = (radioss_cnt_clked==reg_disabled_time_clked) & disable_per & us_p;


    //   
    //PPI automatically start TXEN/RXEN
    //TXEN_task_p    = reg_ppis_clked & PPI_TIMERCC0_TXEN_Msk  ? TIMER_compare0_event_p : reg_TXEN_task_p_clked;
    //RXEN_task_p    = reg_ppis_clked & PPI_TIMERCC0_RXEN_Msk  ? TIMER_compare0_event_p : reg_RXEN_task_p_clked;
    ppi_TXEN_task_p    = reg_chen_clked & PPI_CHEN_CH20_Msk ? TIMER_compare0_event_p : 0;//reg_TXEN_task_p;
    ppi_RXEN_task_p    = reg_chen_clked & PPI_CHEN_CH21_Msk ? TIMER_compare0_event_p : 0;//reg_RXEN_task_p;
    TXEN_task_p = ppi_TXEN_task_p | reg_TXEN_task_p;
    RXEN_task_p = ppi_RXEN_task_p | reg_RXEN_task_p;

    ppi_TIMER_capture1_task_p = reg_chen_clked & PPI_CHEN_CH26_Msk ? ADDRESS_event_p : 0;//reg_TIMER_capture1_task_p;
    ppi_TIMER_capture2_task_p = reg_chen_clked & PPI_CHEN_CH27_Msk ? END_event_p     : 0;//reg_TIMER_capture2_task_p;
    ppi_TIMER_capture3_task_p = reg_chen_clked & PPI_CHEN_CH4_Msk  ? ADDRESS_event_p : 0;//reg_TIMER_capture3_task_p;
    TIMER_capture0_task_p = reg_TIMER_capture0_task_p;
    TIMER_capture1_task_p = ppi_TIMER_capture1_task_p | reg_TIMER_capture1_task_p;
    TIMER_capture2_task_p = ppi_TIMER_capture2_task_p | reg_TIMER_capture2_task_p;
    TIMER_capture3_task_p = ppi_TIMER_capture3_task_p | reg_TIMER_capture3_task_p;
    TIMER_START_task_p = reg_TIMER_START_task_p;
    TIMER_STOP_task_p = reg_TIMER_STOP_task_p;
    TIMER_CLEAR_task_p = reg_TIMER_CLEAR_task_p;

    //shorts
    sh_START_task_p   = reg_shorts_clked & RADIO_SHORTS_READY_START_Msk   ? READY_event_p : 0;//reg_START_task_p_clked;
    ppi_START_task_p = reg_chen_clked & PPI_CHEN_CH31_Msk ? RTC_compare0_event_p : 0;//sh_START_task_p;
    START_task_p = sh_START_task_p | ppi_START_task_p | reg_START_task_p;

    sh_DISABLE_task_p = reg_shorts_clked & RADIO_SHORTS_END_DISABLE_Msk   ? END_event_p : 0;//reg_DISABLE_task_p_clked;
    ppi_DISABLE_task_p = reg_chen_clked & PPI_CHEN_CH5_Msk ? TIMER_compare3_event_p : 0;//sh_DISABLE_task_p;
    DISABLE_task_p = sh_DISABLE_task_p | ppi_DISABLE_task_p | reg_DISABLE_task_p;




  
}