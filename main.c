#include <stdio.h>
#include <stdlib.h>

#include "reg.h"
#include "fetch.h"
#include "opcode_define.h"
//#include "codebus.h"
#include "decode.h"
#include "execu.h"
#include "ext_write_coderam.h"
#include "regfile.h"
#include "clint.h"
#include "itcmmerge.h"
#include "dtcmmerge.h"
#include "regfilemerge.h"

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
    itcmmergeFIFO_clked =0xff;
    dtcmmergeFIFO_clked =0xff;
    regfilemergeFIFO_clked =0xff;

}

int main(int argc, char *argv[])
{
    int i;

    printf("generate trace waveform file: riscv.vcd\n");
    FILE *vcdfp = fopen("riscv.vcd", "w");

    //printf("Hello world!\n");
    //initilize
    setup();
    //
    if (argc==2){
        downloadCode(argv[1]);
        downloadstart=1;
    }
    else{
        init_rom();
    }
    //
    dumpvcdheader(vcdfp);
    //dumpvars(clockcnt, vcdfp);


    while(1)
    {

        //firstclk = (clockcnt==0);
        //
        // 4-pipeline stage

        //for settle down the combination signal
        for (i=0;i<25;i++){

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



            /*
            regwbus();

            codebus();

            databus();

            memwb_bus();

            rs1bus();

            rs2bus();
            */

        }


        //
        //debug_cpuinfo();
        dumpvars(clockcnt, vcdfp);

        //check execption
        if (exe_dec_ilg_clked){
            printf("STOP by detect illigal instruction\n");
            fclose(vcdfp);
            return(1);
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
        
        //
        clockcnt++;
        //
        downloadstart=0;
        //
        //for debug
        //if (clockcnt >= 0x627){
        //    printf("stop\n");
        //}
        //if (clockcnt >= 0x63f) return(1);
        if (clockcnt >= 0x487c) return(1);
        //if (fetpc_clked == 0x8000025e) return(1);
        //if (downloadcomplete) return(1);

    }

    return 0;
}
