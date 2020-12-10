#include "ifubussplit.h"
#include "fetch.h"

void ifubussplit()
{
    int i;

    //it is for 2 target case, 
    //if more targets, should assign value to SPLITTARGETNUM-1 index
    ifusplit_TARGETBASE[0] = 0x80; //itcm
    //ifusplit_TARGETBASE[1] = 0x90; //dtcm

    //ifu come from fetch
    ifusplit_i_bus_cmd_valid = ifu_cmd_valid;
    ifu_cmd_ready = ifusplit_i_bus_cmd_ready;
    ifusplit_i_bus_cmd_read = ifu_cmd_read;
    ifusplit_i_bus_cmd_adr = ifu_cmd_adr;
    ifusplit_i_bus_cmd_data = 0; //ifu_cmd_data;
    ifusplit_i_bus_cmd_rwbyte = ifu_cmd_rwbyte;
    ifu_rsp_read  = ifusplit_i_bus_rsp_read;
    ifu_rsp_valid = ifusplit_i_bus_rsp_valid;
    ifu_rsp_rdata = ifusplit_i_bus_rsp_rdata;
    ifusplit_i_bus_rsp_ready = ifu_rsp_ready;
    //ifu_rsp_rden = ifusplit_i_bus_rsp_rden;
    //ifu_rsp_regidx = ifusplit_i_bus_rsp_regidx;

    //
    //dont accept command if fifo is full
    real_ifusplit_i_bus_cmd_valid = (!ifutransacFIFOfull) & ifusplit_i_bus_cmd_valid;
    //find matching base address except last ifusplit_o_bus_cmd_valid
    for (i=0;i<IFUSPLITTARGETNUM-1;i++)
    {
        ifusplit_o_bus_cmd_valid[i] = (ifusplit_i_bus_cmd_adr>>24)==ifusplit_TARGETBASE[i] ? real_ifusplit_i_bus_cmd_valid : 0;
        ifusplit_o_bus_cmd_read[i] = ifusplit_o_bus_cmd_valid[i] ? ifusplit_i_bus_cmd_read : 0;
        ifusplit_o_bus_cmd_adr[i] = ifusplit_o_bus_cmd_valid[i] ? ifusplit_i_bus_cmd_adr : 0;
        ifusplit_o_bus_cmd_data[i] = ifusplit_o_bus_cmd_valid[i] ? ifusplit_i_bus_cmd_data : 0;
        ifusplit_o_bus_cmd_rwbyte[i] = ifusplit_o_bus_cmd_valid[i] ? ifusplit_i_bus_cmd_rwbyte : 0;
    }
    //
    //check all previous index ifusplit_o_bus_cmd_valid
    ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1]=0;
    for (i=0;i<IFUSPLITTARGETNUM-1;i++)
    {
        ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] = ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1]|ifusplit_o_bus_cmd_valid[i];
    }
    //if all previous index dont match, last one target is selected
    ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] = (!ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1]) & real_ifusplit_i_bus_cmd_valid;
    ifusplit_o_bus_cmd_read[IFUSPLITTARGETNUM-1] = ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] ? ifusplit_i_bus_cmd_read : 0;
    ifusplit_o_bus_cmd_adr[IFUSPLITTARGETNUM-1]  = ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] ? ifusplit_i_bus_cmd_adr : 0;
    ifusplit_o_bus_cmd_data[IFUSPLITTARGETNUM-1] = ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] ? ifusplit_i_bus_cmd_data : 0;
    ifusplit_o_bus_cmd_rwbyte[IFUSPLITTARGETNUM-1] = ifusplit_o_bus_cmd_valid[IFUSPLITTARGETNUM-1] ? ifusplit_i_bus_cmd_rwbyte : 0;

    //
    ifutransacFIFO_wen=ifusplit_i_bus_cmd_ready & ifusplit_i_bus_cmd_valid & ifusplit_i_bus_cmd_read;
    ifutransacFIFO_wid=0;
    for (i=0;i<IFUSPLITTARGETNUM;i++)
    {
    //    ifutransacFIFO_wen =  ifutransacFIFO_wen | (ifusplit_o_bus_cmd_valid[i] & ifusplit_o_bus_cmd_ready[i]);
    //    ifutransacFIFO_wid =  ifutransacFIFO_wid | ((ifusplit_o_bus_cmd_valid[i] & ifusplit_o_bus_cmd_ready[i]) ? i : 0);
        ifutransacFIFO_wid = ifutransacFIFO_wid | (ifusplit_o_bus_cmd_valid[i] ? i :0);
    }
    // accept command and write id into ifutransacFIFO                       
    //ifusplit_i_bus_cmd_ready = ifutransacFIFO_wen;
    ifutransacFIFO = ifutransacFIFO_wen ? ifutransacFIFO_wid : ifutransacFIFO_clked[ifutransacFIFO_widx_clked];
    nxtwrapped_ifutransacFIFO_widx = ((ifutransacFIFO_widx_clked==(IFUSPLIFIFODEPTH-1)) ? 0 :  ifutransacFIFO_widx_clked+1);
    ifutransacFIFO_widx = ifutransacFIFO_wen ? nxtwrapped_ifutransacFIFO_widx : 
                            ifutransacFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    ifutransacFIFOfull = (nxtwrapped_ifutransacFIFO_widx==ifutransacFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    ifutransacFIFOempty = (ifutransacFIFO_widx_clked==ifutransacFIFO_ridx_clked);
    ifutransacFIFO_rid = ifusplit_i_bus_cmd_valid & (!ifusplit_i_bus_cmd_read) ? ifutransacFIFO_wid : //for write bypass 
                         ifutransacFIFOempty ? ifutransacFIFO_wid : ifutransacFIFO_clked[ifutransacFIFO_ridx_clked];
    
    ifusplit_i_bus_rsp_read =0;
    ifusplit_i_bus_rsp_valid=0;
    ifusplit_i_bus_rsp_rdata=0;
    for (i=0;i<IFUSPLITTARGETNUM;i++)
    {
        ifusplit_i_bus_rsp_read  = ifusplit_i_bus_rsp_read  | (ifutransacFIFO_rid==i ? ifusplit_o_bus_rsp_read[i]  : 0) ;
        ifusplit_i_bus_rsp_valid = ifusplit_i_bus_rsp_valid | (ifutransacFIFO_rid==i ? ifusplit_o_bus_rsp_valid[i] : 0) ;
        ifusplit_i_bus_rsp_rdata = ifusplit_i_bus_rsp_rdata | (ifutransacFIFO_rid==i ? ifusplit_o_bus_rsp_rdata[i] : 0) ;
        ifusplit_o_bus_rsp_ready[i] = ifutransacFIFO_rid==i ? ifusplit_i_bus_rsp_ready : 0;
    }

    //rsp accept and move ifutransacFIFO_ridx to next item
    ifutransacFIFO_ren = ifusplit_i_bus_rsp_valid & ifusplit_i_bus_rsp_ready & ifusplit_i_bus_rsp_read;
    ifutransacFIFO_ridx = ifutransacFIFO_ren ? ((ifutransacFIFO_ridx_clked==(IFUSPLIFIFODEPTH-1)) ? 0 :  ifutransacFIFO_ridx_clked+1) : 
                            ifutransacFIFO_ridx_clked;


    //
    ifu2biu_cmd_valid = ifusplit_o_bus_cmd_valid[1];
    ifusplit_o_bus_cmd_ready[1] = ifu2biu_cmd_ready & ifu2biu_cmd_valid;
    ifu2biu_cmd_read = ifusplit_o_bus_cmd_read[1];
    ifu2biu_cmd_adr = ifusplit_o_bus_cmd_adr[1];
    ifu2biu_cmd_data = ifusplit_o_bus_cmd_data[1];
    ifu2biu_cmd_rwbyte = ifusplit_o_bus_cmd_rwbyte[1];
    ifusplit_o_bus_rsp_read[1]  = ifu2biu_rsp_read;
    ifusplit_o_bus_rsp_valid[1] = ifu2biu_rsp_valid;
    ifusplit_o_bus_rsp_rdata[1] = ifu2biu_rsp_rdata;
    ifu2biu_rsp_ready = ifusplit_o_bus_rsp_ready[1];

    //
    ifu2itcm_cmd_valid = ifusplit_o_bus_cmd_valid[0];
    ifusplit_o_bus_cmd_ready[0] = ifu2itcm_cmd_ready & ifu2itcm_cmd_valid;
    ifu2itcm_cmd_read = ifusplit_o_bus_cmd_read[0];
    ifu2itcm_cmd_adr = ifusplit_o_bus_cmd_adr[0];
    ifu2itcm_cmd_data = ifusplit_o_bus_cmd_data[0];
    ifu2itcm_cmd_rwbyte = ifusplit_o_bus_cmd_rwbyte[0];
    ifusplit_o_bus_rsp_read[0]  = ifu2itcm_rsp_read;
    ifusplit_o_bus_rsp_valid[0] = ifu2itcm_rsp_valid;
    ifusplit_o_bus_rsp_rdata[0] = ifu2itcm_rsp_rdata;
    ifu2itcm_rsp_ready = ifusplit_o_bus_rsp_ready[0];

    //
    ifusplit_i_bus_cmd_ready = ifusplit_o_bus_cmd_ready[0]|ifusplit_o_bus_cmd_ready[1];
}