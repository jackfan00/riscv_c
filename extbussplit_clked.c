#include "extbussplit.h"

void extbussplit_clked()
{
    //FIFO
    //write first
    exttransacFIFO_clked[exttransacFIFO_widx_clked] = exttransacFIFO ;
    extregfileidxFIFO_clked[exttransacFIFO_widx_clked] = extregfileidxFIFO;
    extregfilerdenFIFO_clked[exttransacFIFO_widx_clked] = extregfilerdenFIFO;

    //update widx
    exttransacFIFO_widx_clked = exttransacFIFO_widx;

    //read second
    exttransacFIFO_ridx_clked = exttransacFIFO_ridx;


}