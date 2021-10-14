#include <stdio.h>
#include "myradio.h"
#include "myscvr.h"

void myradioreg_setup()
{
    REG64 radiobase;
    REG64 ppibase;
    NRF_RADIO_Type radiost;
    NRF_PPI_Type ppist;
    radiobase = &radiost + NRF_RADIO_BASE;
    ppibase = &ppist + NRF_PPI_BASE;
    RADIO_FREQUENCY_ADDR = &(radiost.FREQUENCY) - radiobase;
    RADIO_SHORTS_ADDR = &(radiost.SHORTS) - radiobase;
    RADIO_PACKETPTR_ADDR = &(radiost.PACKETPTR) - radiobase;
    RADIO_BCC_ADDR = &(radiost.BCC) - radiobase;
    RADIO_INTENSET_ADDR = &(radiost.INTENSET) - radiobase;
    RADIO_INTENCLR_ADDR = &(radiost.INTENCLR) - radiobase;
    RADIO_TXEN_ADDR = &(radiost.TASKS_TXEN) - radiobase;
    RADIO_RXEN_ADDR = &(radiost.TASKS_RXEN) - radiobase;
    RADIO_START_ADDR = &(radiost.TASKS_START) - radiobase;
    RADIO_DISABLE_ADDR = &(radiost.TASKS_DISABLE) - radiobase;
    RADIO_STOP_ADDR = &(radiost.TASKS_STOP) - radiobase;
    RADIO_STATE_ADDR = &(radiost.STATE) - radiobase;
    RADIO_EVENTS_READY_ADDR = &(radiost.EVENTS_READY) - radiobase;
    RADIO_EVENTS_END_ADDR = &(radiost.EVENTS_END) - radiobase;
    RADIO_EVENTS_ADDRESS_ADDR = &(radiost.EVENTS_ADDRESS) - radiobase;
    RADIO_EVENTS_PAYLOAD_ADDR = &(radiost.EVENTS_PAYLOAD) - radiobase;
    RADIO_EVENTS_DISABLED_ADDR = &(radiost.EVENTS_DISABLED) - radiobase;
    PPI_CHEN_ADDR = &(ppist.CHEN) - ppibase;
    PPI_CHENSET_ADDR = &(ppist.CHENSET) - ppibase;
    PPI_CHENCLR_ADDR = &(ppist.CHENCLR) - ppibase;
    //
    RADIO_RAMPUP_TXTIME_ADDR = &(radiost.RESERVED[0]) - radiobase;
    RADIO_RAMPUP_RXTIME_ADDR = &(radiost.RESERVED[1]) - radiobase;
    RADIO_DISABLED_TIME_ADDR = &(radiost.RESERVED[2]) - radiobase;
    RADIO_PYLEN_ADDR = &(radiost.RESERVED[3]) - radiobase;
    RADIO_ACCESS_ADDR = &(radiost.RESERVED[4]) - radiobase;

}

void myradioreg()
{
    BIT END_eventip_p;
    BIT ADDRESS_eventip_p;
    BIT DISABLED_eventip_p;
    REG32 radioss_intenset;
    REG32 radioss_intenclr;

    //radioss event
    READY_event    = radio_regcs & radio_regw & (radio_regwadr==RADIO_EVENTS_READY_ADDR)    ? radio_regwdata&0x01 : READY_event_p    | READY_event_clked;
    END_event      = radio_regcs & radio_regw & (radio_regwadr==RADIO_EVENTS_END_ADDR)      ? radio_regwdata&0x01 : END_event_p      | END_event_clked;
    ADDRESS_event  = radio_regcs & radio_regw & (radio_regwadr==RADIO_EVENTS_ADDRESS_ADDR)  ? radio_regwdata&0x01 : ADDRESS_event_p  | ADDRESS_event_clked;
    PAYLOAD_event  = radio_regcs & radio_regw & (radio_regwadr==RADIO_EVENTS_PAYLOAD_ADDR)  ? radio_regwdata&0x01 : PAYLOAD_event_p  | PAYLOAD_event_clked;
    DISABLED_event = radio_regcs & radio_regw & (radio_regwadr==RADIO_EVENTS_DISABLED_ADDR) ? radio_regwdata&0x01 : DISABLED_event_p | DISABLED_event_clked;

    END_eventip = END_event_clked & ((reg_radioss_inten_clked & RADIO_INTENCLR_END_Msk)!=0);
    ADDRESS_eventip = ADDRESS_event_p & ((reg_radioss_inten_clked & RADIO_INTENCLR_ADDRESS_Msk)!=0);
    DISABLED_eventip = DISABLED_event_p & ((reg_radioss_inten_clked & RADIO_INTENCLR_DISABLED_Msk)!=0);
    READY_eventip = READY_event_p & ((reg_radioss_inten_clked & RADIO_INTENCLR_READY_Msk)!=0);
    PAYLOAD_eventip = PAYLOAD_event_p & ((reg_radioss_inten_clked & RADIO_INTENCLR_PAYLOAD_Msk)!=0);

    //radio interrupt pending
    radioss_ip = END_eventip|ADDRESS_eventip|DISABLED_eventip|READY_eventip|PAYLOAD_eventip;
//
    radio_cmd_ready = (!radio_rsp_valid) | (radio_rsp_valid&radio_rsp_ready);
    radio_regcs = radio_cmd_valid & radio_cmd_ready;// ? 1 : 0;
    radio_regw = !radio_cmd_read;
    radio_regwadr = radio_cmd_adr;
    radio_regwdata = radio_cmd_data;

    reg_rampup_txtime = radio_regcs & radio_regw & (radio_regwadr==RADIO_RAMPUP_TXTIME_ADDR) ? radio_regwdata : reg_rampup_txtime_clked;
    reg_rampup_rxtime = radio_regcs & radio_regw & (radio_regwadr==RADIO_RAMPUP_RXTIME_ADDR) ? radio_regwdata : reg_rampup_rxtime_clked;
    reg_disabled_time = radio_regcs & radio_regw & (radio_regwadr==RADIO_DISABLED_TIME_ADDR) ? radio_regwdata : reg_disabled_time_clked;
    reg_pylen         = radio_regcs & radio_regw & (radio_regwadr==RADIO_PYLEN_ADDR) ? radio_regwdata : reg_pylen_clked;
    reg_accessaddr    = radio_regcs & radio_regw & (radio_regwadr==RADIO_ACCESS_ADDR) ? radio_regwdata : reg_accessaddr_clked;

    reg_frequency = radio_regcs & radio_regw & (radio_regwadr==(RADIO_FREQUENCY_ADDR)) ? radio_regwdata : reg_frequency_clked;
    reg_shorts = radio_regcs & radio_regw & (radio_regwadr==RADIO_SHORTS_ADDR) ? radio_regwdata : reg_shorts_clked;
    reg_packetptr = radio_regcs & radio_regw & (radio_regwadr==RADIO_PACKETPTR_ADDR) ? radio_regwdata : reg_packetptr_clked;
    reg_bcc = radio_regcs & radio_regw & (radio_regwadr==RADIO_BCC_ADDR) ? radio_regwdata : reg_bcc_clked;
    //interrupt reg
    radioss_intenset = radio_regcs & radio_regw & (radio_regwadr==RADIO_INTENSET_ADDR) ? radio_regwdata : 0;
    radioss_intenclr = radio_regcs & radio_regw & (radio_regwadr==RADIO_INTENCLR_ADDR) ? radio_regwdata : 0;
    reg_radioss_inten = (reg_radioss_inten_clked | radioss_intenset) | 
            (reg_radioss_inten_clked & (~radioss_intenclr));

    reg_START_task_p         = radio_regcs & radio_regw & (radio_regwadr==RADIO_START_ADDR) ? radio_regwdata&0x01 : 0;
    reg_STOP_task_p          = radio_regcs & radio_regw & (radio_regwadr==RADIO_STOP_ADDR) ? radio_regwdata&0x01 : 0;
    reg_DISABLE_task_p       = radio_regcs & radio_regw & (radio_regwadr==RADIO_DISABLE_ADDR) ? radio_regwdata&0x01 : 0;
    reg_TXEN_task_p          = radio_regcs & radio_regw & (radio_regwadr==RADIO_TXEN_ADDR) ? radio_regwdata&0x01 : 0;
    reg_RXEN_task_p          = radio_regcs & radio_regw & (radio_regwadr==RADIO_RXEN_ADDR) ? radio_regwdata&0x01 : 0;

    reg_chenset = radio_regcs & radio_regw & (radio_regwadr==PPI_CHENSET_ADDR) ? radio_regwdata : 0;
    reg_chenclr = radio_regcs & radio_regw & (radio_regwadr==PPI_CHENCLR_ADDR) ? radio_regwdata : 0;
    reg_chen = radio_regcs & radio_regw & (radio_regwadr==PPI_CHEN_ADDR) ? radio_regwdata :
            (reg_chen_clked | reg_chenset) | 
            (reg_chen_clked & (~reg_chenclr));


    //regrdata
    radio_rdat = 
                (radio_csadr_clked==RADIO_FREQUENCY_ADDR) ? reg_frequency_clked :
                (radio_csadr_clked==RADIO_ACCESS_ADDR) ? reg_accessaddr : 
                (radio_csadr_clked==RADIO_RAMPUP_TXTIME_ADDR) ? reg_rampup_txtime_clked :
                (radio_csadr_clked==RADIO_RAMPUP_RXTIME_ADDR) ? reg_rampup_rxtime_clked :
                (radio_csadr_clked==RADIO_SHORTS_ADDR) ? reg_shorts_clked :
                (radio_csadr_clked==RADIO_DISABLED_TIME_ADDR) ? reg_disabled_time_clked :
                (radio_csadr_clked==RADIO_PYLEN_ADDR) ? reg_pylen_clked :
                (radio_csadr_clked==RADIO_BCC_ADDR) ? reg_bcc_clked :
                (radio_csadr_clked==RADIO_INTENSET_ADDR) ? reg_radioss_inten_clked :
                (radio_csadr_clked==RADIO_INTENCLR_ADDR) ? reg_radioss_inten_clked :
                (radio_csadr_clked==RADIO_STATE_ADDR) ? radioss_state_clked : 
                (radio_csadr_clked==RADIO_IP_ADDR) ? radioss_ip : 
                (radio_csadr_clked==PPI_CHEN_ADDR) ? reg_chen_clked :
                (radio_csadr_clked==PPI_CHENSET_ADDR) ? reg_chen_clked :
                (radio_csadr_clked==PPI_CHENCLR_ADDR) ? reg_chen_clked :
                timer_rdat;

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


}