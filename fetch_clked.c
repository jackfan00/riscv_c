#include "fetch.h"

void fetch_clked()
{
    //fetpc_clked corresponding to fetchIR, not fetchIR_clked
    fetpc_clked = pc;
    fetchIR_clked = fetchIR;
    memIR_hi16_clked = memIR_hi16;
    //branchjmp_hipart_clked = branchjmp_hipart;

    //
    if (new_midnxtpc_part2_fg)
        new_midnxtpc_part2_fg_clked = 1;
    else if (ifu2mem_cmd_valid & ifu2mem_cmd_ready)
        new_midnxtpc_part2_fg_clked = 0;

}
