#include "itcmmerge.h"

void itcmmerge_clked()
{
    //FIFO
    //write first
    itcmmergeFIFO_clked[itcmmergeFIFO_widx] = itcmmergeFIFO ;
    //itcmmergeFIFO_clked = itcmmergeFIFO ;
    itcmmergeFIFO_widx_clked = itcmmergeFIFO_widx;

    //read second
    itcmmergeFIFO_ridx_clked = itcmmergeFIFO_ridx;

    //roundrobin arbitor
    itcmmerge_ifupri_clked = itcmmerge_ifupri;
    itcmmerge_extpri_clked = itcmmerge_extpri;

    itcmmergeFIFOempty_clked = itcmmergeFIFOempty;

}