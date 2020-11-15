#include <stdio.h>

#include "reg.h"
//#include "memorybus_clked.h"
#include "codebus.h"


void codebus_clked()
{

//local


int i;
    //
    for (i=0;i<CODEARBIT_NUM;i++){
        if (i_codebus_grt[i]){
           // printf("codebus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
        i_codebus_grt_clked[i] = i_codebus_grt[i];
    }


    if (code_rspid_fifo_ren & code_rspid_fifo_empty_clked & (!code_rspid_fifo_wen)){
        printf("codebus Error:fifo read empty\n");
    }
    if (code_rspid_fifo_wen & code_rspid_fifo_full_clked){
        printf("codebus Error:fifo write full\n");
    }

    if (code_rspid_fifo_wen){
        code_rspid_fifo[code_rspid_fifo_wadr] = w_code_rspid;
        code_rspid_fifo_wadr_clked = code_rspid_fifo_wadr >= RSPFIFOSIZE-1 ? 0 : code_rspid_fifo_wadr+1;
        //code_rspid_fifo_full_clked = (code_rspid_fifo_wadr_clked==code_rspid_fifo_radr);
        code_rspid_fifo_empty_clked =0;
    }
    if (code_rspid_fifo_ren){
        //r_code_rspid = code_rspid_fifo[code_rspid_fifo_radr];
        code_rspid_fifo_radr_clked = code_rspid_fifo_radr >= RSPFIFOSIZE-1 ? 0 :code_rspid_fifo_radr+1;
        //code_rspid_fifo_empty_clked = (code_rspid_fifo_wadr==code_rspid_fifo_radr_clked);
        code_rspid_fifo_full_clked =0;
    }

    //
    code_rspid_fifo_wadr = code_rspid_fifo_wadr_clked;
    code_rspid_fifo_radr = code_rspid_fifo_radr_clked;
    if (code_rspid_fifo_wen){
        code_rspid_fifo_full_clked = (code_rspid_fifo_wadr_clked==code_rspid_fifo_radr);
    }
    if (code_rspid_fifo_ren){
        code_rspid_fifo_empty_clked = (code_rspid_fifo_wadr==code_rspid_fifo_radr_clked);
    }

    //
    coderamctrl_clked();
}

void coderamctrl_clked()
{
    //
    if (coderam_wrsp_valid){
        coderam_wrsp_per_clked = 0; 
    }
    if (coderam_rrsp_valid){
        coderam_rrsp_per_clked = 0; 
    }        
    //
    if (coderam_cs){
        if (coderam_we){
            coderam[coderam_adr] = coderam_wdat;
            coderam_wrsp_per_clked = 1;
        }
        else{
            coderam_rdat = coderam[coderam_adr];
            coderam_rrsp_per_clked =1;
        }
        // simulate multi-cycle ready case
        ready_cycles_clked = 1;
    }
    else if (coderam_wrsp_per_clked | coderam_rrsp_per_clked){
        ready_cycles_clked++;
    }
    coderam_cs_clked = coderam_cs;
    coderam_we_clked = coderam_we;



//

}
