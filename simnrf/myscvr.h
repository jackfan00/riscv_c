#ifndef NRF51_H
#define NRF51_H

#include "../reg.h"

#define uint32_t REG32
#define     __IM     volatile const            /*!< defines 'read only' permissions      */
#define     __OM     volatile                  /*!< defines 'write only' permissions     */
#define     __IOM    volatile                  /*!< defines 'read / write' permissions   */

/* =========================================================================================================================== */
/* ================                                           RADIO                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief The radio. (RADIO)
  */

typedef struct {                                /*!< (@ 0x40001000) RADIO Structure                                            */
  __OM  uint32_t  TASKS_TXEN;                   /*!< (@ 0x00000000) Enable radio in TX mode.                                   */
  __OM  uint32_t  TASKS_RXEN;                   /*!< (@ 0x00000004) Enable radio in RX mode.                                   */
  __OM  uint32_t  TASKS_START;                  /*!< (@ 0x00000008) Start radio.                                               */
  __OM  uint32_t  TASKS_STOP;                   /*!< (@ 0x0000000C) Stop radio.                                                */
  __OM  uint32_t  TASKS_DISABLE;                /*!< (@ 0x00000010) Disable radio.                                             */
  __OM  uint32_t  TASKS_RSSISTART;              /*!< (@ 0x00000014) Start the RSSI and take one sample of the receive
                                                                    signal strength.                                           */
  __OM  uint32_t  TASKS_RSSISTOP;               /*!< (@ 0x00000018) Stop the RSSI measurement.                                 */
  __OM  uint32_t  TASKS_BCSTART;                /*!< (@ 0x0000001C) Start the bit counter.                                     */
  __OM  uint32_t  TASKS_BCSTOP;                 /*!< (@ 0x00000020) Stop the bit counter.                                      */
  __IM  uint32_t  RESERVED[55];
  __IOM uint32_t  EVENTS_READY;                 /*!< (@ 0x00000100) Ready event.                                               */
  __IOM uint32_t  EVENTS_ADDRESS;               /*!< (@ 0x00000104) Address event.                                             */
  __IOM uint32_t  EVENTS_PAYLOAD;               /*!< (@ 0x00000108) Payload event.                                             */
  __IOM uint32_t  EVENTS_END;                   /*!< (@ 0x0000010C) End event.                                                 */
  __IOM uint32_t  EVENTS_DISABLED;              /*!< (@ 0x00000110) Disable event.                                             */
  __IOM uint32_t  EVENTS_DEVMATCH;              /*!< (@ 0x00000114) A device address match occurred on the last received
                                                                    packet.                                                    */
  __IOM uint32_t  EVENTS_DEVMISS;               /*!< (@ 0x00000118) No device address match occurred on the last
                                                                    received packet.                                           */
  __IOM uint32_t  EVENTS_RSSIEND;               /*!< (@ 0x0000011C) Sampling of the receive signal strength complete.
                                                                    A new RSSI sample is ready for readout at
                                                                    the RSSISAMPLE register.                                   */
  __IM  uint32_t  RESERVED1[2];
  __IOM uint32_t  EVENTS_BCMATCH;               /*!< (@ 0x00000128) Bit counter reached bit count value specified
                                                                    in BCC register.                                           */
  __IM  uint32_t  RESERVED2[53];
  __IOM uint32_t  SHORTS;                       /*!< (@ 0x00000200) Shortcuts for the radio.                                   */
  __IM  uint32_t  RESERVED3[64];
  __IOM uint32_t  INTENSET;                     /*!< (@ 0x00000304) Interrupt enable set register.                             */
  __IOM uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Interrupt enable clear register.                           */
  __IM  uint32_t  RESERVED4[61];
  __IM  uint32_t  CRCSTATUS;                    /*!< (@ 0x00000400) CRC status of received packet.                             */
  __IM  uint32_t  RESERVED5;
  __IM  uint32_t  RXMATCH;                      /*!< (@ 0x00000408) Received address.                                          */
  __IM  uint32_t  RXCRC;                        /*!< (@ 0x0000040C) Received CRC.                                              */
  __IM  uint32_t  DAI;                          /*!< (@ 0x00000410) Device address match index.                                */
  __IM  uint32_t  RESERVED6[60];
  __IOM uint32_t  PACKETPTR;                    /*!< (@ 0x00000504) Packet pointer. Decision point: START task.                */
  __IOM uint32_t  FREQUENCY;                    /*!< (@ 0x00000508) Frequency.                                                 */
  __IOM uint32_t  TXPOWER;                      /*!< (@ 0x0000050C) Output power.                                              */
  __IOM uint32_t  MODE;                         /*!< (@ 0x00000510) Data rate and modulation.                                  */
  __IOM uint32_t  PCNF0;                        /*!< (@ 0x00000514) Packet configuration 0.                                    */
  __IOM uint32_t  PCNF1;                        /*!< (@ 0x00000518) Packet configuration 1.                                    */
  __IOM uint32_t  BASE0;                        /*!< (@ 0x0000051C) Radio base address 0. Decision point: START task.          */
  __IOM uint32_t  BASE1;                        /*!< (@ 0x00000520) Radio base address 1. Decision point: START task.          */
  __IOM uint32_t  PREFIX0;                      /*!< (@ 0x00000524) Prefixes bytes for logical addresses 0 to 3.               */
  __IOM uint32_t  PREFIX1;                      /*!< (@ 0x00000528) Prefixes bytes for logical addresses 4 to 7.               */
  __IOM uint32_t  TXADDRESS;                    /*!< (@ 0x0000052C) Transmit address select.                                   */
  __IOM uint32_t  RXADDRESSES;                  /*!< (@ 0x00000530) Receive address select.                                    */
  __IOM uint32_t  CRCCNF;                       /*!< (@ 0x00000534) CRC configuration.                                         */
  __IOM uint32_t  CRCPOLY;                      /*!< (@ 0x00000538) CRC polynomial.                                            */
  __IOM uint32_t  CRCINIT;                      /*!< (@ 0x0000053C) CRC initial value.                                         */
  __IOM uint32_t  TEST;                         /*!< (@ 0x00000540) Test features enable register.                             */
  __IOM uint32_t  TIFS;                         /*!< (@ 0x00000544) Inter Frame Spacing in microseconds.                       */
  __IM  uint32_t  RSSISAMPLE;                   /*!< (@ 0x00000548) RSSI sample.                                               */
  __IM  uint32_t  RESERVED7;
  __IM  uint32_t  STATE;                        /*!< (@ 0x00000550) Current radio state.                                       */
  __IOM uint32_t  DATAWHITEIV;                  /*!< (@ 0x00000554) Data whitening initial value.                              */
  __IM  uint32_t  RESERVED8[2];
  __IOM uint32_t  BCC;                          /*!< (@ 0x00000560) Bit counter compare.                                       */
  __IM  uint32_t  RESERVED9[39];
  __IOM uint32_t  DAB[8];                       /*!< (@ 0x00000600) Device address base segment.                               */
  __IOM uint32_t  DAP[8];                       /*!< (@ 0x00000620) Device address prefix.                                     */
  __IOM uint32_t  DACNF;                        /*!< (@ 0x00000640) Device address match configuration.                        */
  __IM  uint32_t  RESERVED10[56];
  __IOM uint32_t  OVERRIDE0;                    /*!< (@ 0x00000724) Trim value override register 0.                            */
  __IOM uint32_t  OVERRIDE1;                    /*!< (@ 0x00000728) Trim value override register 1.                            */
  __IOM uint32_t  OVERRIDE2;                    /*!< (@ 0x0000072C) Trim value override register 2.                            */
  __IOM uint32_t  OVERRIDE3;                    /*!< (@ 0x00000730) Trim value override register 3.                            */
  __IOM uint32_t  OVERRIDE4;                    /*!< (@ 0x00000734) Trim value override register 4.                            */
  __IM  uint32_t  RESERVED11[561];
  __IOM uint32_t  POWER;                        /*!< (@ 0x00000FFC) Peripheral power control.                                  */
} NRF_RADIO_Type;                               /*!< Size = 4096 (0x1000)                                                      */

/* =========================================================================================================================== */
/* ================                                          TIMER0                                           ================ */
/* =========================================================================================================================== */


/**
  * @brief Timer 0. (TIMER0)
  */

typedef struct {                                /*!< (@ 0x40008000) TIMER0 Structure                                           */
  __OM  uint32_t  TASKS_START;                  /*!< (@ 0x00000000) Start Timer.                                               */
  __OM  uint32_t  TASKS_STOP;                   /*!< (@ 0x00000004) Stop Timer.                                                */
  __OM  uint32_t  TASKS_COUNT;                  /*!< (@ 0x00000008) Increment Timer (In counter mode).                         */
  __OM  uint32_t  TASKS_CLEAR;                  /*!< (@ 0x0000000C) Clear timer.                                               */
  __OM  uint32_t  TASKS_SHUTDOWN;               /*!< (@ 0x00000010) Shutdown timer.                                            */
  __IM  uint32_t  RESERVED[11];
  __OM  uint32_t  TASKS_CAPTURE[4];             /*!< (@ 0x00000040) Capture Timer value to CC[n] registers.                    */
  __IM  uint32_t  RESERVED1[60];
  __IOM uint32_t  EVENTS_COMPARE[4];            /*!< (@ 0x00000140) Compare event on CC[n] match.                              */
  __IM  uint32_t  RESERVED2[44];
  __IOM uint32_t  SHORTS;                       /*!< (@ 0x00000200) Shortcuts for Timer.                                       */
  __IM  uint32_t  RESERVED3[64];
  __IOM uint32_t  INTENSET;                     /*!< (@ 0x00000304) Interrupt enable set register.                             */
  __IOM uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Interrupt enable clear register.                           */
  __IM  uint32_t  RESERVED4[126];
  __IOM uint32_t  MODE;                         /*!< (@ 0x00000504) Timer Mode selection.                                      */
  __IOM uint32_t  BITMODE;                      /*!< (@ 0x00000508) Sets timer behaviour.                                      */
  __IM  uint32_t  RESERVED5;
  __IOM uint32_t  PRESCALER;                    /*!< (@ 0x00000510) 4-bit prescaler to source clock frequency (max
                                                                    value 9). Source clock frequency is divided
                                                                    by 2^SCALE.                                                */
  __IM  uint32_t  RESERVED6[11];
  __IOM uint32_t  CC[4];                        /*!< (@ 0x00000540) Capture/compare registers.                                 */
  __IM  uint32_t  RESERVED7[683];
  __IOM uint32_t  POWER;                        /*!< (@ 0x00000FFC) Peripheral power control.                                  */
} NRF_TIMER_Type;                               /*!< Size = 4096 (0x1000)                                                      */



/* =========================================================================================================================== */
/* ================                                           RTC0                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief Real time counter 0. (RTC0)
  */

typedef struct {                                /*!< (@ 0x4000B000) RTC0 Structure                                             */
  __OM  uint32_t  TASKS_START;                  /*!< (@ 0x00000000) Start RTC Counter.                                         */
  __OM  uint32_t  TASKS_STOP;                   /*!< (@ 0x00000004) Stop RTC Counter.                                          */
  __OM  uint32_t  TASKS_CLEAR;                  /*!< (@ 0x00000008) Clear RTC Counter.                                         */
  __OM  uint32_t  TASKS_TRIGOVRFLW;             /*!< (@ 0x0000000C) Set COUNTER to 0xFFFFFFF0.                                 */
  __IM  uint32_t  RESERVED[60];
  __IOM uint32_t  EVENTS_TICK;                  /*!< (@ 0x00000100) Event on COUNTER increment.                                */
  __IOM uint32_t  EVENTS_OVRFLW;                /*!< (@ 0x00000104) Event on COUNTER overflow.                                 */
  __IM  uint32_t  RESERVED1[14];
  __IOM uint32_t  EVENTS_COMPARE[4];            /*!< (@ 0x00000140) Compare event on CC[n] match.                              */
  __IM  uint32_t  RESERVED2[109];
  __IOM uint32_t  INTENSET;                     /*!< (@ 0x00000304) Interrupt enable set register.                             */
  __IOM uint32_t  INTENCLR;                     /*!< (@ 0x00000308) Interrupt enable clear register.                           */
  __IM  uint32_t  RESERVED3[13];
  __IOM uint32_t  EVTEN;                        /*!< (@ 0x00000340) Configures event enable routing to PPI for each
                                                                    RTC event.                                                 */
  __IOM uint32_t  EVTENSET;                     /*!< (@ 0x00000344) Enable events routing to PPI. The reading of
                                                                    this register gives the value of EVTEN.                    */
  __IOM uint32_t  EVTENCLR;                     /*!< (@ 0x00000348) Disable events routing to PPI. The reading of
                                                                    this register gives the value of EVTEN.                    */
  __IM  uint32_t  RESERVED4[110];
  __IM  uint32_t  COUNTER;                      /*!< (@ 0x00000504) Current COUNTER value.                                     */
  __IOM uint32_t  PRESCALER;                    /*!< (@ 0x00000508) 12-bit prescaler for COUNTER frequency (32768/(PRESCALER+1)).
                                                                    Must be written when RTC is STOPed.                        */
  __IM  uint32_t  RESERVED5[13];
  __IOM uint32_t  CC[4];                        /*!< (@ 0x00000540) Capture/compare registers.                                 */
  __IM  uint32_t  RESERVED6[683];
  __IOM uint32_t  POWER;                        /*!< (@ 0x00000FFC) Peripheral power control.                                  */
} NRF_RTC_Type;                                 /*!< Size = 4096 (0x1000)                                                      */



/* =========================================================================================================================== */
/* ================                                            PPI                                            ================ */
/* =========================================================================================================================== */


/**
  * @brief PPI_TASKS_CHG [TASKS_CHG] (Channel group tasks.)
  */
typedef struct {
  __OM  uint32_t  EN;                           /*!< (@ 0x00000000) Enable channel group.                                      */
  __OM  uint32_t  DIS;                          /*!< (@ 0x00000004) Disable channel group.                                     */
} PPI_TASKS_CHG_Type;                           /*!< Size = 8 (0x8)                                                            */


/**
  * @brief PPI_CH [CH] (PPI Channel.)
  */
typedef struct {
  __IOM uint32_t  EEP;                          /*!< (@ 0x00000000) Channel event end-point.                                   */
  __IOM uint32_t  TEP;                          /*!< (@ 0x00000004) Channel task end-point.                                    */
} PPI_CH_Type;                                  /*!< Size = 8 (0x8)                                                            */


/**
  * @brief PPI controller. (PPI)
  */

typedef struct {                                /*!< (@ 0x4001F000) PPI Structure                                              */
  __IOM PPI_TASKS_CHG_Type TASKS_CHG[4];        /*!< (@ 0x00000000) Channel group tasks.                                       */
  __IM  uint32_t  RESERVED[312];
  __IOM uint32_t  CHEN;                         /*!< (@ 0x00000500) Channel enable.                                            */
  __IOM uint32_t  CHENSET;                      /*!< (@ 0x00000504) Channel enable set.                                        */
  __IOM uint32_t  CHENCLR;                      /*!< (@ 0x00000508) Channel enable clear.                                      */
  __IM  uint32_t  RESERVED1;
  __IOM PPI_CH_Type CH[16];                     /*!< (@ 0x00000510) PPI Channel.                                               */
  __IM  uint32_t  RESERVED2[156];
  __IOM uint32_t  CHG[4];                       /*!< (@ 0x00000800) Channel group configuration.                               */
} NRF_PPI_Type;                                 /*!< Size = 2064 (0x810)                                                       */

#define PPI_CHEN_CH4_Msk    (0x1UL << 4)
#define PPI_CHEN_CH5_Msk    (0x1UL << 5)
#define PPI_CHEN_CH20_Msk    (0x1UL << 20)
#define PPI_CHEN_CH21_Msk    (0x1UL << 21)
#define PPI_CHEN_CH23_Msk    (0x1UL << 23)
#define PPI_CHEN_CH25_Msk    (0x1UL << 25)
#define PPI_CHEN_CH26_Msk    (0x1UL << 26)
#define PPI_CHEN_CH27_Msk    (0x1UL << 27)
#define PPI_CHEN_CH31_Msk    (0x1UL << 31)
#define RADIO_INTENCLR_READY_Msk (0x1UL << 0)
#define RADIO_INTENCLR_ADDRESS_Msk (0x1UL << 1)
#define RADIO_INTENCLR_PAYLOAD_Msk (0x1UL << 2)
#define RADIO_INTENCLR_END_Msk (0x1UL << 3)
#define RADIO_INTENCLR_DISABLED_Msk (0x1UL << 4)
#define RADIO_INTENSET_READY_Msk (0x1UL << 0)
#define RADIO_INTENSET_ADDRESS_Msk (0x1UL << 1)
#define RADIO_INTENSET_PAYLOAD_Msk (0x1UL << 2)
#define RADIO_INTENSET_END_Msk (0x1UL << 3)
#define RADIO_INTENSET_DISABLED_Msk (0x1UL << 4)
#define RADIO_SHORTS_READY_START_Msk (0x1UL << 0)
#define RADIO_SHORTS_END_DISABLE_Msk (0x1UL << 1)
#define RADIO_SHORTS_DISABLED_TXEN_Msk (0x1UL << 2)
#define RADIO_SHORTS_DISABLED_RXEN_Msk (0x1UL << 3)
#define RADIO_SHORTS_END_START_Msk (0x1UL << 5)

#define TIMER_INTENCLR_COMPARE0_Msk (0x1UL << 16)
#define TIMER_INTENCLR_COMPARE1_Msk (0x1UL << 17)
#define TIMER_INTENCLR_COMPARE2_Msk (0x1UL << 18)
#define TIMER_INTENCLR_COMPARE3_Msk (0x1UL << 19)
#define TIMER_INTENSET_COMPARE0_Msk (0x1UL << 16)
#define TIMER_INTENSET_COMPARE1_Msk (0x1UL << 17)
#define TIMER_INTENSET_COMPARE2_Msk (0x1UL << 18)
#define TIMER_INTENSET_COMPARE3_Msk (0x1UL << 19)

#define RTC_INTENCLR_COMPARE0_Msk (0x1UL << 16)
#define RTC_INTENCLR_COMPARE1_Msk (0x1UL << 17)
#define RTC_INTENCLR_COMPARE2_Msk (0x1UL << 18)
#define RTC_INTENCLR_COMPARE3_Msk (0x1UL << 19)
#define RTC_INTENSET_COMPARE0_Msk (0x1UL << 16)
#define RTC_INTENSET_COMPARE1_Msk (0x1UL << 17)
#define RTC_INTENSET_COMPARE2_Msk (0x1UL << 18)
#define RTC_INTENSET_COMPARE3_Msk (0x1UL << 19)

#define NRF_RADIO_BASE              0x10001000UL
#define NRF_TIMER0_BASE             0x10008000UL
#define NRF_RTC0_BASE               0x1000B000UL
#define NRF_PPI_BASE                0x1001F000UL

#define NRF_RADIO                   ((NRF_RADIO_Type*)         NRF_RADIO_BASE)
#define NRF_TIMER0                  ((NRF_TIMER_Type*)         NRF_TIMER0_BASE)
#define NRF_RTC0                    ((NRF_RTC_Type*)           NRF_RTC0_BASE)
#define NRF_PPI                     ((NRF_PPI_Type*)           NRF_PPI_BASE)

#endif  //NRF51_H


