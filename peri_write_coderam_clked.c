#include "peri_write_coderam.h"


void peri_write_coderam_clked()
{
    randomcycle_clked = downloadstart ? 0 :
                        peri_cmd_valid & peri_cmd_ready ? 0 : 
                        downloadper_clked ? randomcycle_clked+1 : 0;

    codeindex_clked =   downloadstart ? 0 :
                        downloadcomplete ? codeindex_clked :
                        peri_cmd_valid & peri_cmd_ready ? codeindex_clked+1 : codeindex_clked;
    downloadper_clked = downloadstart ? 1 :
                        downloadcomplete ? 0 : downloadper_clked;
}