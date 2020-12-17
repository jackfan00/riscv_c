#include "lif.h"
#include "decode.h"
//#include "regbus.h"
//#include "memwb_bus.h"

//long instruction flag, same pipeline position as execu/decode_clked
// lif_id: 0:div, 1:lsu, 2:mul
//
void lif_clked()
{
    /*******************
    int i;
    REG8 tmp;

    //clear flag after write regs
    if (regw_cs & regw_we){
        //for (i=0;i<LIFSIZE;i++){
        //    if (regw_id==lifid_clked[i] & lifvalid_clked[i])  lifvalid_clked[i] =0;              
        //}
        lifvalid_clked[regw_id*2]=lifvalid_clked[regw_id*2+1];
        lifrdidx_clked[regw_id*2]=lifrdidx_clked[regw_id*2+1];
        lifvalid_clked[regw_id*2+1] =0;
    }

    //scan all to find idle item, this is software method 
    //hardware implementation need to change 
    
    //for debug purpose
    if (lifvalid_clked[dec_lif_id*2] & lifvalid_clked[dec_lif_id*2+1] & dec_lif_cmd){
        printf("Error: more than 2 lifcmd-id %d (0:div, 1:lsu, 2:mul)\n", dec_lif_id);
    }
    //
    if (dec_lif_cmd){
            if (!lifvalid_clked[dec_lif_id*2]){
                lifrdidx_clked[dec_lif_id*2] = rdidx;
                lifvalid_clked[dec_lif_id*2] = 1;
            } 
            else{
                lifrdidx_clked[dec_lif_id*2+1] = rdidx;
                lifvalid_clked[dec_lif_id*2+1] = 1;
            }
    }
    //if (!lifvalid_clked[dec_lif_id] & dec_lif_cmd){
    //    lifvalid_clked[dec_lif_id]= 1;
    //    lifrdidx_clked[dec_lif_id]= rdidx;
    //}
    */

    lif_divrdidx_clked = lif_divrdidx;
    lif_loadrdidx_clked = lif_loadrdidx;
    lif_loadfull_clked = lif_loadfull;

}