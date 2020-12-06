#include "lsubussplit.h"

void lsubussplit_clked()
{
    //FIFO
    //write first
    lsutransacFIFO_clked[lsutransacFIFO_widx_clked] = lsutransacFIFO ;
    lsuregfileidxFIFO_clked[lsutransacFIFO_widx_clked] = lsuregfileidxFIFO;
    lsuregfilerdenFIFO_clked[lsutransacFIFO_widx_clked] = lsuregfilerdenFIFO;

    //update widx
    lsutransacFIFO_widx_clked = lsutransacFIFO_widx;

    //read second
    lsutransacFIFO_ridx_clked = lsutransacFIFO_ridx;


}