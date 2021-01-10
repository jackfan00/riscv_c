#include "regfilemerge.h"

void regfilemerge_clked()
{
    //FIFO
    //write first
    //regfilemergeFIFO_clked[regfilemergeFIFO_widx_clked] = regfilemergeFIFO ;
    regfilemergeFIFO_clked = regfilemergeFIFO ;
    //regfilemergeFIFO_widx_clked = regfilemergeFIFO_widx;

    //read second
    //regfilemergeFIFO_ridx_clked = regfilemergeFIFO_ridx;

    //roundrobin arbitor
    divpri_clked = divpri;
    mulpri_clked = mulpri;
    s2pri_clked = s2pri;

}