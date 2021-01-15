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
    //init_rom();
    //
    //rspid_fifo_wadr_clked = RSPFIFOSIZE-1;
    //code_rspid_fifo_empty_clked =1;
    fetchIR_clked = NOP;
    fetpc_clked = 0x12345678;  //ensure different address from BOOTADDR
    fetch_flush =0;
    firstinst_clked=1;
    clockcnt=0;
    clint_mtimecmp_clked=0xffffffff;
    clint_mtimecmph_clked=0xffffffff;
    //itcmmergeFIFO_clked =0xff;
    biumergeFIFO_ridx_clked=1;
    dtcmmergeFIFO_ridx_clked =1;
    itcmmergeFIFO_ridx_clked=1;
    regfilemergeFIFO_clked =0xff;
    signature_startaddr=0x80002000;

    //UART0
    txuart0_shmptr = simuart(MYKEY_UART0, BUFSIZE_UART0);
    rxuart0_shmptr = txuart0_shmptr + 1;
    *rxuart0_shmptr=(1<<31);  //initialize empty
    //printf("%d--%d\n", (unsigned int)txuart0_shmptr, (unsigned int)rxuart0_shmptr);

}

int main(int argc, char *argv[])
{
    int i, maxconverge_iter;
    char * imcindi;

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
        for (i=0;i<20;i++){

            ext_write_coderam();

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

            /*
            regwbus();

            codebus();

            databus();

            memwb_bus();

            rs1bus();

            rs2bus();
            */
            
            if (isconverge()){
                if (maxconverge_iter<i)
                    maxconverge_iter =  i;
                break;
            };
            
        }

        if (i==20){
            printf("Error:not converge\n");
            exit(2);
        }


        //
#ifdef DUMPVCD
if (clockcnt >=344400) {
        dumpvars(clockcnt, vcdfp);
}
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
        ext_write_coderam_clked();
        testfinishcheck_clked();
        exitcheck_clked();
        perfcheck_clked();

        uart_clked();
        
        //
        clockcnt++;
        //
        downloadstart=0;
        //
        //for debug
        //if (clockcnt >= 0x627){
        //    printf("stop\n");
        //}
        //if (clockcnt >= 348400) break;
        //if (clockcnt >= 0x416d) {
        //    break;
        //    printf("dddd\n");
        //}
        //if (fetpc_clked == 0x80000d40){
        //    printf("dddd %x\n",clockcnt);
        //    break;
        //} 
        //if (downloadcomplete) break;

    }

#ifdef DUMPVCD
    fclose(vcdfp);
#endif    
    return 0;
}
