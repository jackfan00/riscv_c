#include "memwb_bus.h"

void memwb_bus_clked()
{
int i;
    //
    for (i=0;i<WBARBIT_NUM;i++){
        if (i_memwb_bus_grt[i]){
            //printf("memwb_bus: cmd arbitor select =%d=, at clock counter =%d= \n", i, clockcnt);
        }
        i_memwb_bus_grt_clked[i] = i_memwb_bus_cmd_ready[i] ? 0 : i_memwb_bus_grt[i];
    }

}