#include "dtcmmerge.h"

void dtcmmerge_clked()
{
    //FIFO
    //write first
    dtcmmergeFIFO_clked[dtcmmergeFIFO_widx] = dtcmmergeFIFO ;
    //dtcmmergeFIFO_clked = dtcmmergeFIFO;
    dtcmmergeFIFO_widx_clked = dtcmmergeFIFO_widx;

    //read second
    dtcmmergeFIFO_ridx_clked = dtcmmergeFIFO_ridx;

    //roundrobin arbitor
    dtcmmerge_extpri_clked = dtcmmerge_extpri;

    dtcmmergeFIFOempty_clked = dtcmmergeFIFOempty;

}