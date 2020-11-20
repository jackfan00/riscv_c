#include "lif.h"
#include "decode.h"
#include "regbus.h"
#include "memwb_bus.h"

//long instruction flag, same pipeline position as execu/decode_clked
// lif_id: 0:div, 1:lsu, 2:mul
//
void lif_clked()
{
    int i;
    REG8 tmp;

    //clear flag after write regs
    if (regw_cs & regw_we){
        //for (i=0;i<LIFSIZE;i++){
        //    if (regw_id==lifid_clked[i] & lifvalid_clked[i])  lifvalid_clked[i] =0;              
        //}
        lifvalid_clked[regw_id]=0;
    }

    //scan all to find idle item, this is software method 
    //hardware implementation need to change 
    
    //
    lifvalid_clked[dec_lif_id]= dec_lif_cmd;
    lifrdidx_clked[dec_lif_id]= rdidx;

}