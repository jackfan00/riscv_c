
#define PERI_CYCLES 3
#include "ext_write_coderam.h"
#include "downloadCode.h"
#include "itcmmerge.h"


void ext_write_coderam()
{
    downloadcomplete = (codeindex_clked>download_codesize);
    if (downloadper_clked){
        ext_cmd_valid = (randomcycle_clked>PERI_CYCLES);
        ext_cmd_read =0;
        ext_cmd_addr = HEXcodeaddr[codeindex_clked];
        ext_cmd_wdata = HEXcodedata[codeindex_clked];
    }
    else{
        ext_cmd_valid =0;
    }

    //
    //
    ext2itcm_cmd_valid  = ext_cmd_valid;
    ext2itcm_cmd_read   = ext_cmd_read;
    ext2itcm_cmd_adr    = ext_cmd_addr;
    ext2itcm_cmd_data   = ext_cmd_wdata;
    ext2itcm_cmd_rwbyte = 0xf;
    ext_cmd_ready      = ext2itcm_cmd_ready;
    ext2itcm_rsp_ready  = 1;

}
