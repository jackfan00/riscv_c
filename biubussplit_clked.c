#include "biubussplit.h"

void biubussplit_clked()
{
    //FIFO
    //write first
    biutransacFIFO_clked[biutransacFIFO_widx_clked] = biutransacFIFO ;
    biutransacFIFO_widx_clked = biutransacFIFO_widx;

    //read second
    biutransacFIFO_ridx_clked = biutransacFIFO_ridx;
}