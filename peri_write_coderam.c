
#define PERI_CYCLES 3
#include "peri_write_coderam.h"
#include "downloadCode.h"


void peri_write_coderam()
{
    downloadcomplete = (codeindex_clked>=download_codesize);
    if (downloadper_clked){
        peri_cmd_valid = (randomcycle_clked>PERI_CYCLES);
        peri_cmd_read =0;
        peri_cmd_addr = HEXcodeaddr[codeindex_clked];
        peri_cmd_wdata = HEXcodedata[codeindex_clked];

    }
    else{
        peri_cmd_valid =0;
    }
}
