#include "ext_write_coderam.h"


void ext_write_coderam_clked()
{
    randomcycle_clked = downloadstart ? 0 :
                        ext_cmd_valid & ext_cmd_ready ? 0 : 
                        downloadper_clked ? randomcycle_clked+1 : 0;

    codeindex_clked =   downloadstart ? 0 :
                        downloadcomplete ? codeindex_clked :
                        ext_cmd_valid & ext_cmd_ready ? codeindex_clked+1 : codeindex_clked;
    downloadper_clked = downloadstart ? 1 :
                        downloadcomplete ? 0 : downloadper_clked;
}