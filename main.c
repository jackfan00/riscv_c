#include <stdio.h>
#include <stdlib.h>

#include "reg.h"
#include "fetch.h"
#include "opcode_define.h"
#include "codebus.h"
#include "decode.h"
#include "execu.h"

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
        printf("0x%08x ", regsarray[i]);
        if ((i%8)==7) printf("\n");
    }
}

void setup()
{
    init_rom();
    //
    //rspid_fifo_wadr_clked = RSPFIFOSIZE-1;
    code_rspid_fifo_empty_clked =1;
    fetchIR_clked = NOP;
    fetpc_clked = 0x12345678;  //ensure different address from BOOTADDR
    fetch_flush =0;
    firstinst_clked=1;
}

int main()
{
    int i;
    //printf("Hello world!\n");
    //initilize
    setup();


    clockcnt=0;
    while(1)
    {

        //firstclk = (clockcnt==0);
        //
        // 4-pipeline stage

        //for settle down the combination signal
        for (i=0;i<7;i++){

            fetch();

            decode();

            execu();

            mul();

            memwb();  // memory access and write-back at the same stage

            regwbus();

            codebus();

            databus();

            memwb_bus();

            rs1bus();

            rs2bus();

        }


        //
        debug_cpuinfo();

        //check execption
        if (exe_dec_ilg_clked){
            printf("STOP by detect illigal instruction\n");
            return(1);
        }

        // flipflop

       // memwb_clked();
       // order is important
        regwbus_clked();
        execu_clked();
        decode_clked();
        fetch_clked();
//
       //order is not important
        codebus_clked();
        databus_clked();
        memwb_bus_clked();
        mul_clked();
        


        //
        clockcnt++;


    }

    return 0;
}
