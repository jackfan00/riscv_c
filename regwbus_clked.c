#include "regbus.h"
#include "decode.h"

void regwbus_clked()
{
    int i;
    //
    for (i=0;i<REGARBIT_NUM;i++){
        i_regwbus_grt_clked[i] = i_regwbus_grt[i];
    }

    if (regw_cs & regw_we){
        regsarray[regw_adr] = regw_wdat;
    }
}
