#include "regbus.h"
#include "decode.h"

void regwbus_clked()
{
    int i;
    //
    for (i=0;i<REGARBIT_NUM;i++){
        if (i_regwbus_grt[i]){
          //  printf("regwbus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
        if (i_rs1bus_grt[i]){
          //  printf("rs1bus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
        if (i_rs2bus_grt[i]){
          //  printf("rs2bus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
         i_regwbus_grt_clked[i] = i_regwbus_cmd_ready[i] ? 0 : i_regwbus_grt[i];
         i_rs1bus_grt_clked[i] = i_rs1bus_cmd_ready[i] ? 0 : i_rs1bus_grt[i];
         i_rs2bus_grt_clked[i] = i_rs2bus_cmd_ready[i] ? 0 : i_rs2bus_grt[i];
    }

    if (regw_cs & regw_we){
       // printf("regwbus: regwrite addr =0x%x=, data =0x%x=, at clock counter =%d= \n", regw_adr, regw_wdat, clockcnt);
        regsarray[regw_adr] = regw_wdat;
    }
}
