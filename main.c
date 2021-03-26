#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define DUMPVCD
#include "opcode_define.h"
#include "dumpvars.h"
#include "downloadCode.h"
#include "init_rom.h"
#include "reg.h"
#include "fetch.h"
#include "decode.h"
#include "execu.h"
#include "lif.h"
#include "mul.h"
#include "divrem.h"
#include "memwb.h"
#include "ext_write_coderam.h"
#include "extbussplit.h"
#include "regfile.h"
#include "csrreg.h"
#include "clint.h"
#include "plic.h"
#include "itcm.h"
#include "dtcm.h"
#include "peripheral.h"
#include "ifubussplit.h"
#include "lsubussplit.h"
#include "biubussplit.h"
#include "biumerge.h"
#include "itcmmerge.h"
#include "dtcmmerge.h"
#include "regfilemerge.h"
#include "testfinishcheck.h"
#include "exitcheck.h"
#include "perfcheck.h"
#include "uart.h"
#include "gpio.h"
#include "pwm.h"
#include "simhw/simuart.h"
#include "isconverge.h"

void debug_cpuinfo(){
    int i;
    printf("clockcnt, pc--------, instrution, regs 1-31\n");
    printf("%08d, 0x%08x, 0x%08x", clockcnt, fetpc_clked, fetchIR);
    if (fet_ras_pop){
        printf(", fetch ras pop 0x%08x", branchjmp_pc);
    }
    if (dec_ras_push_clked){
        printf(", execu ras push 0x%08x", exe_res);
    }
    printf("\n");

    for (i=0;i<32;i++){
        printf("0x%08x ", regfileffs_clked[i]);
        if ((i%8)==7) printf("\n");
    }
}


void setup()
{
    int i;
    //init_rom();
    //
    //rspid_fifo_wadr_clked = RSPFIFOSIZE-1;
    //code_rspid_fifo_empty_clked =1;
    fetchIR_clked = NOP;
    fetpc_clked = 0x12345678;  //ensure different address from BOOTADDR
    //fetch_flush =0;
    firstinst_clked=1;
    clockcnt=0;
    clint_mtimecmp_clked=0xffffffff;
    clint_mtimecmph_clked=0xffffffff;
    //plic 
    for (i=1;i<PLIC_INTNUMBER;i++){
        gateway_enable_clked[i]=1;
    }
    
    //itcmmergeFIFO_clked =0xff;
    biumergeFIFO_ridx_clked=1;
    dtcmmergeFIFO_ridx_clked =1;
    itcmmergeFIFO_ridx_clked=1;
    regfilemergeFIFO_clked =0xff;

    //tests
    signature_startaddr=0x80002000;

    //UART0
    uart_rxdata_clked = 0x80000000; //empty
    txuart0_shmptr = simuart(MYKEY_UART0, BUFSIZE_UART0);
    rxuart0_shmptr = txuart0_shmptr + 1;
    *rxuart0_shmptr=(1<<31);  //initialize empty
    //GPIO
    gpio_shmptr = txuart0_shmptr + 2;
    *gpio_shmptr = 0xffffffff;
    *(gpio_shmptr+1) = 0xffffffff;
    //printf("%d--%d\n", (unsigned int)txuart0_shmptr, (unsigned int)rxuart0_shmptr);

}

int main(int argc, char *argv[])
{
    int i, maxconverge_iter;
    char * imcindi;
    BIT debug;

    maxconverge_iter=0;

#ifdef DUMPVCD
    printf("generate trace waveform file: riscv.vcd\n");
    FILE *vcdfp = fopen("/home/jack/tmp/riscv.vcd", "w");
    dumpvcdheader(vcdfp);
#endif
    //printf("Hello world!\n");
    //initilize
    setup();
    //
    if (argc>=2){
        downloadCode(argv[1]);
        downloadstart=1;
        testcase = strdup(argv[1]);
        //
        PC_WRITE_TOHOST       =0x80000086;  //e200 test
        HAS_REFERENCEOUT      =0;
        if (argc>=3){
            HAS_REFERENCEOUT      =1;
            referenceout = strdup(argv[2]);
            printf("referenceout=%s\n", referenceout);
            imcindi = strstr(referenceout, "rv32imc");
            //

            if (imcindi==NULL){
                PC_WRITE_TOHOST       =0x80000040;  //COMPLIANCE_IM_TEST
            }
            else{
                PC_WRITE_TOHOST       =0x80000036;  //COMPLIANCE_IMC_TEST
            }
        }
        if (argc>=4){
            signature_startaddr = (REG32)strtoul(trimwhitespace(argv[3]), NULL, 16);
            printf("signature_startaddr=%08x\n", signature_startaddr);
        }
    }
    else{
        init_rom();
    }
    //


    while(1)
    {

        //firstclk = (clockcnt==0);
        //
        // 4-pipeline stage

        //for settle down the combination signal
        for (i=0;i<30;i++){

            ext_write_coderam();
            extbussplit();

            fetch();

            decode();

            execu();

            mul();

            divrem();

            memwb();  // memory access and write-back at the same stage

            ifubussplit();
            lsubussplit();
            biumerge();
            biubussplit();
            plic();
            clint();
            peripheral();
            itcmmerge();
            itcm();
            dtcmmerge();
            dtcm();
            regfilemerge();
            regfile();
            csrreg();

            perfcheck();

            uart();
            gpio();
            pwm();

            /*
            regwbus();

            codebus();

            databus();

            memwb_bus();

            rs1bus();

            rs2bus();
            */
           debug = (i>20);
            if (isconverge(debug)){
                if (maxconverge_iter<i){
                    maxconverge_iter =  i;
                    //printf("INFO:maxconverge_iter=%d\n", maxconverge_iter);
                }    
                break;
            };
            
        }

        if (i>=30){
            printf("Error:not converge,%d, maxconverge_iter=%d\n",clockcnt, maxconverge_iter);
            exit(2);
        }


        //
#ifdef DUMPVCD
//if ((clockcnt >=39000)){//} && clockcnt<=17000) || (clockcnt<=1000)) {
if ((clockcnt >=16974000)){//&&(clockcnt <=2318800)){
        dumpvars(clockcnt, vcdfp);
}
//if ((clockcnt >=7782815)&&(clockcnt <=7784815)){
//        dumpvars(clockcnt, vcdfp);
//}
#endif
        //check execption
        //if (exe_dec_ilg_clked){
        //    printf("STOP by detect illigal instruction\n");
        //    break;
        //}
        //
        if (testfinishcheck()){
            break;
        }
        if (exitcheck()){
            //
            printf("=====performance check=======\n");
            printf("ifu_2cyc_counter=%d\n", ifu_2cyc_counter_clked);
            printf("branchjmp_counter=%d\n", branchjmp_counter_clked);
            printf("branch_fail_counter=%d\n", branch_fail_counter_clked);
            printf("branch_success_counter=%d\n", branch_success_counter_clked);
            printf("jalr_fail_counter=%d\n", jalr_fail_counter_clked);
            printf("jalr_success_counter=%d\n", jalr_success_counter_clked);
            printf("lsu2itcm_counter=%d\n", lsu2itcm_counter_clked);
            printf("div_rwaw_counter=%d\n", div_rwaw_counter_clked);
            printf("load_rwaw_counter=%d\n", load_rwaw_counter_clked);
            printf("lsu_load_counter=%d\n", lsu_load_counter_clked);
            printf("dec_stall_counter=%d\n", dec_stall_counter_clked);
            printf("=============================\n");
            //
            printf("exitcheck break, clockcnt=%d, maxconverge_iter=%d\n", clockcnt, maxconverge_iter);
            break;
        }
        // flipflop

       // memwb_clked();
       // order is important
       // regwbus_clked();
        regfile_clked();
        csrreg_clked();
        execu_clked();
        decode_clked();
        fetch_clked();
//
       //order is not important
       // codebus_clked();
       // databus_clked();
       // memwb_bus_clked();
        mul_clked();
        divrem_clked();
        lif_clked();

        ifubussplit_clked();
        lsubussplit_clked();
        biumerge_clked();
        biubussplit_clked();
        plic_clked();
        clint_clked();
        peripheral_clked();
        itcmmerge_clked();
        itcm_clked();
        dtcmmerge_clked();
        dtcm_clked();
        regfilemerge_clked();

        //
        extbussplit_clked();
        ext_write_coderam_clked();
        testfinishcheck_clked();
        exitcheck_clked();
        perfcheck_clked();

        uart_clked();
        gpio_clked();
        pwm_clked();
        
        //
        clockcnt++;
        //
        downloadstart=0;
        //
        //for debug
        //if (clockcnt >= 0x627){
        //    printf("stop\n");
        //}
        //if (clockcnt >= 2457000) break;
        //if (clockcnt >= 0x416d) {
        //    break;
        //    printf("dddd\n");
        //}
        /*
        if (downloadcomplete & exe_validir_clked&(exe_pc_clked == 0x8000000c)){
            printf("%d:indicate restart\n",clockcnt);
        //    break;
        } */

        if (exe_validir_clked&(exe_pc_clked == 0x8001a0f6)){
            printf("%d:ble_hs_dbg_event_disp\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000b424)){
            printf("%d:ble_ll_scan_timer_cb\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000ce70)){
            printf("%d:ble_ll_xcvr_rfclk_timer_exp\n",clockcnt);
        //    break;
        }
        if (exe_validir_clked&(exe_pc_clked == 0x8000c2a4)){
            printf("%d:ble_ll_sched_run\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005798)){
            printf("%d:ble_ll_adv_flags_clear\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000d0ae)){
            printf("%d:ble_phy_rfclk_enable\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005b94)){
            printf("%d:ble_ll_adv_sm_stop\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80003576)){
            printf("%d:os_cputime_timer_init\n",clockcnt);
        //    break;
        } 
        
        
        if (exe_validir_clked&(exe_pc_clked == 0x8000b63a)){
            printf("%d:ble_ll_scan_common_init\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005568)){
            printf("%d:ble_ll_init\n",clockcnt);
        //    break;
        } 
        
        if (exe_validir_clked&(exe_pc_clked == 0x8000caae)){
            printf("%d:ble_ll_sched_init\n",clockcnt);
        //    break;
        } 
        /*
        if (exe_validir_clked&(exe_pc_clked == 0x800000ca){
            printf("%d:SystemInit\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80000530){
            printf("%d:os_init\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80002f2c){
            printf("%d:hal_bsp_init\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000356a){
            printf("%d:os_cputime_init\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800032f6){
            printf("%d:hal_timer_config\n",clockcnt);
        //    break;
        } */
        if (exe_validir_clked&(exe_pc_clked == 0x8000340e)){
            printf("%d:hal_timer_start_at\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000325e)){
            printf("%d:fe310_pwm_cmp0_handler\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000329e)){
            printf("%d:fe310_pwm_cmp1_handler\n",clockcnt);
        //    break;
        } 
        
        if (exe_validir_clked&(exe_pc_clked == 0x800031d0)){
            printf("%d:fe310_tmr_check_first\n",clockcnt);
        //    break;
        }
         
        if (exe_validir_clked&(exe_pc_clked == 0x800034e8)){
            printf("%d:plic_enable_interrupt\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800058a4)){
            printf("%d:ble_ll_adv_set_sched\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000c68e)){
            printf("%d:ble_ll_sched_adv_new\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80003596)){
            printf("%d:os_cputime_timer_start\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000ceb8)){
            printf("%d:ble_ll_xcvr_rfclk_timer_start\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800031a4)){
            printf("%d:hal_timer_cnt\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005a18)){
            printf("%d:ble_ll_adv_tx_start_cb\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800059c4)){
            printf("%d:ble_ll_adv_tx_done\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000cf9c)){
            printf("%d:ble_phy_tx\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005434)){
            printf("%d:ble_ll_state_set\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000590a)){
            printf("%d:ble_ll_adv_legacy_pdu_make\n",clockcnt);
        //    break;
        } 
         
        if (exe_validir_clked&(exe_pc_clked == 0x8000350e)){
            printf("%d:plic_disable_interrupt\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000359e)){
            printf("%d:os_cputime_get32\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800060d2)){
            printf("%d:ble_ll_adv_set_enable\n",clockcnt);
        //    break;
        } 
        /*
        //if (exe_validir_clked&(exe_pc_clked == 0x8000320e)){
        //    printf("%d:fe310_tmr_cbs\n",clockcnt);
        //    break;
        //} 
        if (exe_validir_clked&(exe_pc_clked == 0x800034c0)){
            printf("%d:plic_set_handler\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80003596)){
            printf("%d:os_cputime_timer_stop\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x800035a0)){
            printf("%d:os_cputime_usecs_to_ticks\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x80005b90)){
            printf("%d:ble_ll_adv_sm_stop\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000c99a)){
            printf("%d:ble_ll_sched_rmv_elem\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000ca4a)){
            printf("%d:ble_ll_sched_rfclk_chk_restart\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000d082)){
            printf("%d:ble_phy_disable\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8000d8e4)){
            printf("%d:ble_gap_adv_start\n",clockcnt);
        //    break;
        } 
        */
        if (exe_validir_clked&(exe_pc_clked == 0x80009e0e)){
            printf("%d:ble_ll_hci_cmd_proc\n",clockcnt);
        //    break;
        } 
        if (exe_validir_clked&(exe_pc_clked == 0x8001b600)){
            printf("%d:ble_hci_trans_ll_evt_tx\n",clockcnt);
        //    break;
        } 
        
        if (exe_validir_clked&(exe_pc_clked == 0x8000546e)){
            printf("%d:ble_ll_reset\n",clockcnt);
        //    break;
        } 
        
        //if (exe_validir_clked&(exe_pc_clked == 0x80002ca6)){
        //    printf("%d:console_out_nolock\n",clockcnt);
        //    break;
        //} 
        //if (downloadcomplete) break;

    }

#ifdef DUMPVCD
    fclose(vcdfp);
#endif    
    return 0;
}
