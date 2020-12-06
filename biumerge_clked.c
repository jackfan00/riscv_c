#include "biumerge.h"

void biumerge_clked()
{
    //FIFO
    //write first
    biumergeFIFO_clked[biumergeFIFO_widx_clked] = biumergeFIFO ;
    biumergeFIFO_widx_clked = biumergeFIFO_widx;

    //read second
    biumergeFIFO_ridx_clked = biumergeFIFO_ridx;

    //roundrobin arbitor
    biumerge_ifupri_clked = biumerge_ifupri;

}