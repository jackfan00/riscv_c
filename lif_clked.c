#include "lif.h"
#include "decode.h"
#include "regbus.h"
#include "memwb_bus.h"

//long instruction flag, same pipeline position as execu/decode_clked
void lif_clked()
{
    int i;
    REG8 tmp;

    if (regw_cs & regw_we){
        for (i=0;i<LIFSIZE;i++){
            if (regw_id==lifid_clked[i] & lifvalid_clked[i])  lifvalid_clked[i] =0;              
        }    
    }

    //scan all to find idle item, this is software method 
    //hardware implementation need to change 
    if (dec_lif_cmd){
        for (i=0;i<LIFSIZE;i++){
               if (!lifvalid_clked[i]){
                lifvalid_clked[i] = 1;
                lifrdidx_clked[i] = rdidx;
                lifid_clked[i] = dec_lif_id;  
                break;
               }
        }
        lifbuffull = (i==LIFSIZE);
    }

}