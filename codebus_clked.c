#include <stdio.h>

#include "reg.h"
//#include "memorybus_clked.h"
#include "codebus.h"


void codebus_clked()
{

//local
REG8 nxt_wadr;
REG8 nxt_radr;


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
    if (code_rspid_fifo_wen & code_rspid_fifo_full_clked & (!code_rspid_fifo_ren)){
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
    nxt_wadr = code_rspid_fifo_wadr_clked >= RSPFIFOSIZE-1 ? 0 : code_rspid_fifo_wadr_clked+1;
    nxt_radr = code_rspid_fifo_radr_clked >= RSPFIFOSIZE-1 ? 0 : code_rspid_fifo_radr_clked+1;
    //if (code_rspid_fifo_wen){
        code_rspid_fifo_full_clked = (nxt_wadr==code_rspid_fifo_radr_clked);
    //}
    //if (code_rspid_fifo_ren){
        code_rspid_fifo_empty_clked = (nxt_radr==code_rspid_fifo_wadr_clked);
    //}

    //
    coderamctrl_clked();
}

void coderamctrl_clked()
{
    //
    //if (coderam_wrsp_valid){
    //    coderam_wrsp_per_clked = 0; 
    //}
    //if (coderam_rrsp_valid){
    //    coderam_rrsp_per_clked = 0; 
    //}        
    if (o_codebus_rsp_valid){
        coderam_rrsp_per_clked = 0; 
        //coderam_rspvalid_cycles_clked =0;
    }        
    //
    if (o_codebus_cmd_valid & o_codebus_cmd_ready){
        coderam_cmdready_cycles_clked=0;
    }
    else if (o_codebus_cmd_valid){
        coderam_cmdready_cycles_clked++;
    }
    else{
        coderam_cmdready_cycles_clked=0;
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
        coderam_rspvalid_cycles_clked = 1;
    }
    else if (coderam_rrsp_per_clked){
        coderam_rspvalid_cycles_clked++;
    }
    //coderam_cs_clked = coderam_cs;
    //coderam_we_clked = coderam_we;



//

}
