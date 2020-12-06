#include "lsubussplit.h"
#include "execu.h"

void lsubussplit()
{
    int i;

    //it is for 3 target case, 
    //if more targets, should assign value to SPLITTARGETNUM-1 index
    lsusplit_TARGETBASE[0] = 0x80; //itcm
    lsusplit_TARGETBASE[1] = 0x90; //dtcm

    //lsu come from execu
    lsusplit_i_bus_cmd_valid = lsu_cmd_valid;
    lsu_cmd_ready = lsusplit_i_bus_cmd_ready;
    lsusplit_i_bus_cmd_read = lsu_cmd_read;
    lsusplit_i_bus_cmd_adr = lsu_cmd_adr;
    lsusplit_i_bus_cmd_data = lsu_cmd_data;
    lsusplit_i_bus_cmd_rwbyte = lsu_cmd_rwbyte;
    lsu_rsp_valid = lsusplit_i_bus_rsp_valid;
    lsu_rsp_rdata = lsusplit_i_bus_rsp_rdata;
    lsusplit_i_bus_rsp_ready = lsu_rsp_ready;
    lsu_rsp_rden = lsusplit_i_bus_rsp_rden;
    lsu_rsp_regidx = lsusplit_i_bus_rsp_regidx;

    //
    //dont accept command if fifo is full
    real_lsusplit_i_bus_cmd_valid = !lsutransacFIFOfull & lsusplit_i_bus_cmd_valid;
    //find matching base address except last lsusplit_o_bus_cmd_valid
    for (i=0;i<LSUSPLITTARGETNUM-1;i++)
    {
        lsusplit_o_bus_cmd_valid[i] = (lsusplit_i_bus_cmd_adr>>24)==lsusplit_TARGETBASE[i] ? real_lsusplit_i_bus_cmd_valid : 0;
        lsusplit_o_bus_cmd_read[i] = lsusplit_o_bus_cmd_valid[i] ? lsusplit_i_bus_cmd_read : 0;
        lsusplit_o_bus_cmd_adr[i] = lsusplit_o_bus_cmd_valid[i] ? lsusplit_i_bus_cmd_adr : 0;
        lsusplit_o_bus_cmd_data[i] = lsusplit_o_bus_cmd_valid[i] ? lsusplit_i_bus_cmd_data : 0;
        lsusplit_o_bus_cmd_rwbyte[i] = lsusplit_o_bus_cmd_valid[i] ? lsusplit_i_bus_cmd_rwbyte : 0;
    }
    //
    //check all previous index lsusplit_o_bus_cmd_valid
    lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1]=0;
    for (i=0;i<LSUSPLITTARGETNUM-1;i++)
    {
        lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] = lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1]|lsusplit_o_bus_cmd_valid[i];
    }
    //if all previous index dont match, last one target is selected
    lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] = (!lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1]) & real_lsusplit_i_bus_cmd_valid;
    lsusplit_o_bus_cmd_read[LSUSPLITTARGETNUM-1] = lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] ? lsusplit_i_bus_cmd_read : 0;
    lsusplit_o_bus_cmd_adr[LSUSPLITTARGETNUM-1]  = lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] ? lsusplit_i_bus_cmd_adr : 0;
    lsusplit_o_bus_cmd_data[LSUSPLITTARGETNUM-1] = lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] ? lsusplit_i_bus_cmd_data : 0;
    lsusplit_o_bus_cmd_rwbyte[LSUSPLITTARGETNUM-1] = lsusplit_o_bus_cmd_valid[LSUSPLITTARGETNUM-1] ? lsusplit_i_bus_cmd_rwbyte : 0;

    //
    lsutransacFIFO_wen=0;
    for (i=0;i<LSUSPLITTARGETNUM;i++)
    {
        lsutransacFIFO_wen =  lsutransacFIFO_wen | (lsusplit_o_bus_cmd_valid[i] & lsusplit_o_bus_cmd_ready[i]);
        lsutransacFIFO_wid =  lsutransacFIFO_wid | ((lsusplit_o_bus_cmd_valid[i] & lsusplit_o_bus_cmd_ready[i]) ? i : 0);
    }
    // accept command and write id into lsutransacFIFO                       
    lsusplit_i_bus_cmd_ready = lsutransacFIFO_wen;
    lsutransacFIFO = lsutransacFIFO_wen ? lsutransacFIFO_wid : lsutransacFIFO_clked[lsutransacFIFO_widx_clked];
    nxtwrapped_lsutransacFIFO_widx = ((lsutransacFIFO_widx_clked==(LSUSPLIFIFODEPTH-1)) ? 0 :  lsutransacFIFO_widx_clked+1);
    lsutransacFIFO_widx = lsutransacFIFO_wen ? nxtwrapped_lsutransacFIFO_widx : 
                            lsutransacFIFO_widx_clked;
    //store regfile info
    lsuregfileidxFIFO = lsutransacFIFO_wen ? lsu_cmd_regidx : lsuregfileidxFIFO_clked[lsutransacFIFO_widx_clked];
    lsuregfilerdenFIFO = lsutransacFIFO_wen ? lsu_cmd_rden : lsuregfilerdenFIFO_clked[lsutransacFIFO_widx_clked];

    //fifo full condition : if next fifo write reach read-idx
    lsutransacFIFOfull = (nxtwrapped_lsutransacFIFO_widx==lsutransacFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    lsutransacFIFOempty = (lsutransacFIFO_widx_clked==lsutransacFIFO_ridx_clked);
    lsutransacFIFO_rid = lsutransacFIFOempty ? lsutransacFIFO_wid : lsutransacFIFO_clked[lsutransacFIFO_ridx_clked];

    //addition info
    lsusplit_i_bus_rsp_regidx= lsutransacFIFOempty ? lsu_cmd_regidx : lsuregfileidxFIFO_clked[lsutransacFIFO_ridx_clked];
    lsusplit_i_bus_rsp_rden  = lsutransacFIFOempty ? lsu_cmd_rden   : lsuregfilerdenFIFO_clked[lsutransacFIFO_ridx_clked];

    //
    lsusplit_i_bus_rsp_valid=0;
    lsusplit_i_bus_rsp_rdata=0;
    for (i=0;i<LSUSPLITTARGETNUM;i++)
    {
        lsusplit_i_bus_rsp_valid = lsusplit_i_bus_rsp_valid | (lsutransacFIFO_rid==i ? lsusplit_o_bus_rsp_valid[i] : 0) ;
        lsusplit_i_bus_rsp_rdata = lsusplit_i_bus_rsp_rdata | (lsutransacFIFO_rid==i ? lsusplit_o_bus_rsp_rdata[i] : 0) ;
        lsusplit_o_bus_rsp_ready[i] = lsutransacFIFO_rid==i ? lsusplit_i_bus_rsp_ready : 0;
    }

    //rsp accept and move lsutransacFIFO_ridx to next item
    lsutransacFIFO_ren = lsusplit_i_bus_rsp_valid & lsusplit_i_bus_rsp_ready;
    lsutransacFIFO_ridx = lsutransacFIFO_ren ? ((lsutransacFIFO_ridx_clked==(LSUSPLIFIFODEPTH-1)) ? 0 :  lsutransacFIFO_ridx_clked+1) : 
                            lsutransacFIFO_ridx_clked;


    //
    lsu2biu_cmd_valid = lsusplit_o_bus_cmd_valid[2];
    lsusplit_o_bus_cmd_ready[2] = lsu2biu_cmd_ready & lsu2biu_cmd_valid;
    lsu2biu_cmd_read = lsusplit_o_bus_cmd_read[2];
    lsu2biu_cmd_adr = lsusplit_o_bus_cmd_adr[2];
    lsu2biu_cmd_data = lsusplit_o_bus_cmd_data[2];
    lsu2biu_cmd_rwbyte = lsusplit_o_bus_cmd_rwbyte[2];
    lsusplit_o_bus_rsp_valid[2] = lsu2biu_rsp_valid;
    lsusplit_o_bus_rsp_rdata[2] = lsu2biu_rsp_rdata;
    lsu2biu_rsp_ready = lsusplit_o_bus_rsp_ready[2];

    //
    lsu2dtcm_cmd_valid = lsusplit_o_bus_cmd_valid[1];
    lsusplit_o_bus_cmd_ready[1] = lsu2dtcm_cmd_ready & lsu2dtcm_cmd_valid;
    lsu2dtcm_cmd_read = lsusplit_o_bus_cmd_read[1];
    lsu2dtcm_cmd_adr = lsusplit_o_bus_cmd_adr[1];
    lsu2dtcm_cmd_data = lsusplit_o_bus_cmd_data[1];
    lsu2dtcm_cmd_rwbyte = lsusplit_o_bus_cmd_rwbyte[1];
    lsusplit_o_bus_rsp_valid[1] = lsu2dtcm_rsp_valid;
    lsusplit_o_bus_rsp_rdata[1] = lsu2dtcm_rsp_rdata;
    lsu2dtcm_rsp_ready = lsusplit_o_bus_rsp_ready[1];

    //
    lsu2itcm_cmd_valid = lsusplit_o_bus_cmd_valid[0];
    lsusplit_o_bus_cmd_ready[0] = lsu2itcm_cmd_ready & lsu2itcm_cmd_valid;
    lsu2itcm_cmd_read = lsusplit_o_bus_cmd_read[0];
    lsu2itcm_cmd_adr = lsusplit_o_bus_cmd_adr[0];
    lsu2itcm_cmd_data = lsusplit_o_bus_cmd_data[0];
    lsu2itcm_cmd_rwbyte = lsusplit_o_bus_cmd_rwbyte[0];
    lsusplit_o_bus_rsp_valid[0] = lsu2itcm_rsp_valid;
    lsusplit_o_bus_rsp_rdata[0] = lsu2itcm_rsp_rdata;
    lsu2itcm_rsp_ready = lsusplit_o_bus_rsp_ready[0];


}