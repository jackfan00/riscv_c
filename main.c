#include <stdio.h>
#include <stdlib.h>

#include "reg.h"
#include "fetch.h"
#include "opcode_define.h"
#include "codebus.h"

void setup()
{
    init_rom();
    //
    //rspid_fifo_wadr_clked = RSPFIFOSIZE-1;
    code_rspid_fifo_empty_clked =1;
    fetchIR_clked = NOP;
    fetpc_clked = 0x12345;  //ensure different address from BOOTADDR
    fetch_flush =0;
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

        firstclk = (clockcnt==0);
        //
        // 4-pipeline stage

        //for settle down the combination signal
        for (i=0;i<7;i++){

            fetch();

            decode();

            execu();

            memwb();  // memory access and write-back at the same stage

            regwbus();

            codebus();

            databus();

            rs1bus();

            rs2bus();

        }


        //
        // flipflop

       // memwb_clked();
        regwbus_clked();
        execu_clked();
        decode_clked();
        fetch_clked();
//
        codebus_clked();
        databus_clked();


        //
        clockcnt++;


    }

    return 0;
}
