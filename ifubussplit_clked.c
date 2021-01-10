#include "ifubussplit.h"

void ifubussplit_clked()
{
    //FIFO
    //write first
    ifutransacFIFO_clked[ifutransacFIFO_widx_clked] = ifutransacFIFO ;
    ifutransacFIFO_widx_clked = ifutransacFIFO_widx;

    //read second
    ifutransacFIFO_ridx_clked = ifutransacFIFO_ridx;
}