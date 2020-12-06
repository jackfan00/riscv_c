#include "biubussplit.h"
#include "biumerge.h"
#include "plic.h"
#include "clint.h"

void biubussplit()
{
    int i;

    //it is for 3 target case, 
    //if more targets, should assign value to SPLITTARGETNUM-1 index
    biusplit_TARGETBASE[0] = 0x0c; //plic
    biusplit_TARGETBASE[1] = 0x02; //clint
    biusplit_TARGETBASE[2] = 0x10; //periperal
    biusplit_TARGETBASE[3] = 0x20; //flash mempry mapping

    //
    biusplit_i_bus_cmd_valid = biumerge_o_cmd_valid;
    biusplit_i_bus_cmd_read = biumerge_o_cmd_read;
    biusplit_i_bus_cmd_adr = biumerge_o_cmd_adr;
    biusplit_i_bus_cmd_data = biumerge_o_cmd_data;
    biusplit_i_bus_cmd_rwbyte = biumerge_o_cmd_rwbyte;
    biumerge_o_cmd_ready = biusplit_i_bus_cmd_ready ;
    biumerge_o_rsp_valid = biusplit_i_bus_rsp_valid ;
    biumerge_o_rsp_rdata = biusplit_i_bus_rsp_rdata ;
    biusplit_i_bus_rsp_ready = biumerge_o_rsp_ready ;

    //dont accept command if fifo is full
    real_biusplit_i_bus_cmd_valid = !biutransacFIFOfull & biusplit_i_bus_cmd_valid;
    //find matching base address except last biusplit_o_bus_cmd_valid
    for (i=0;i<BIUSPLITTARGETNUM-1;i++)
    {
        biusplit_o_bus_cmd_valid[i] = (biusplit_i_bus_cmd_adr>>24)==biusplit_TARGETBASE[i] ? real_biusplit_i_bus_cmd_valid : 0;
        biusplit_o_bus_cmd_read[i] = biusplit_o_bus_cmd_valid[i] ? biusplit_i_bus_cmd_read : 0;
        biusplit_o_bus_cmd_adr[i] = biusplit_o_bus_cmd_valid[i] ? biusplit_i_bus_cmd_adr : 0;
        biusplit_o_bus_cmd_data[i] = biusplit_o_bus_cmd_valid[i] ? biusplit_i_bus_cmd_data : 0;
        biusplit_o_bus_cmd_rwbyte[i] = biusplit_o_bus_cmd_valid[i] ? biusplit_i_bus_cmd_rwbyte : 0;
    }
    //
    //check all previous index biusplit_o_bus_cmd_valid
    biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1]=0;
    for (i=0;i<BIUSPLITTARGETNUM-1;i++)
    {
        biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] = biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1]|biusplit_o_bus_cmd_valid[i];
    }
    //if all previous index dont match, last one target is selected
    biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] = (!biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1]) & real_biusplit_i_bus_cmd_valid;
    biusplit_o_bus_cmd_read[BIUSPLITTARGETNUM-1] = biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] ? biusplit_i_bus_cmd_read : 0;
    biusplit_o_bus_cmd_adr[BIUSPLITTARGETNUM-1]  = biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] ? biusplit_i_bus_cmd_adr : 0;
    biusplit_o_bus_cmd_data[BIUSPLITTARGETNUM-1] = biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] ? biusplit_i_bus_cmd_data : 0;
    biusplit_o_bus_cmd_rwbyte[BIUSPLITTARGETNUM-1] = biusplit_o_bus_cmd_valid[BIUSPLITTARGETNUM-1] ? biusplit_i_bus_cmd_rwbyte : 0;

    //
    biutransacFIFO_wen=0;
    for (i=0;i<BIUSPLITTARGETNUM;i++)
    {
        biutransacFIFO_wen =  biutransacFIFO_wen | (biusplit_o_bus_cmd_valid[i] & biusplit_o_bus_cmd_ready[i]);
        biutransacFIFO_wid =  biutransacFIFO_wid | ((biusplit_o_bus_cmd_valid[i] & biusplit_o_bus_cmd_ready[i]) ? i : 0);
    }
    // accept command and write id into biutransacFIFO                       
    biusplit_i_bus_cmd_ready = biutransacFIFO_wen;
    biutransacFIFO = biutransacFIFO_wen ? biutransacFIFO_wid : biutransacFIFO_clked[biutransacFIFO_widx_clked];
    nxtwrapped_biutransacFIFO_widx = ((biutransacFIFO_widx_clked==(BIUSPLIFIFODEPTH-1)) ? 0 :  biutransacFIFO_widx_clked+1);
    biutransacFIFO_widx = biutransacFIFO_wen ? nxtwrapped_biutransacFIFO_widx : 
                            biutransacFIFO_widx_clked;

    //fifo full condition : if next fifo write reach read-idx
    biutransacFIFOfull = (nxtwrapped_biutransacFIFO_widx==biutransacFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    biutransacFIFOempty = (biutransacFIFO_widx_clked==biutransacFIFO_ridx_clked);
    biutransacFIFO_rid = biutransacFIFOempty ? biutransacFIFO_wid : biutransacFIFO_clked[biutransacFIFO_ridx_clked];
    biusplit_i_bus_rsp_valid=0;
    biusplit_i_bus_rsp_rdata=0;
    for (i=0;i<BIUSPLITTARGETNUM;i++)
    {
        biusplit_i_bus_rsp_valid = biusplit_i_bus_rsp_valid | (biutransacFIFO_rid==i ? biusplit_o_bus_rsp_valid[i] : 0) ;
        biusplit_i_bus_rsp_rdata = biusplit_i_bus_rsp_rdata | (biutransacFIFO_rid==i ? biusplit_o_bus_rsp_rdata[i] : 0) ;
        biusplit_o_bus_rsp_ready[i] = biutransacFIFO_rid==i ? biusplit_i_bus_rsp_ready : 0;
    }

    //rsp accept and move biutransacFIFO_ridx to next item
    biutransacFIFO_ren = biusplit_i_bus_rsp_valid & biusplit_i_bus_rsp_ready;
    biutransacFIFO_ridx = biutransacFIFO_ren ? ((biutransacFIFO_ridx_clked==(BIUSPLIFIFODEPTH-1)) ? 0 :  biutransacFIFO_ridx_clked+1) : 
                            biutransacFIFO_ridx_clked;


    //
    plic_cmd_valid = biusplit_o_bus_cmd_valid[0];
    biusplit_o_bus_cmd_ready[0] = plic_cmd_ready & plic_cmd_valid;
    plic_cmd_read = biusplit_o_bus_cmd_read[0];
    plic_cmd_adr = biusplit_o_bus_cmd_adr[0];
    plic_cmd_data = biusplit_o_bus_cmd_data[0];
    biusplit_o_bus_rsp_valid[0] = plic_rsp_valid;
    biusplit_o_bus_rsp_rdata[0] = plic_rsp_rdata;
    plic_rsp_ready = biusplit_o_bus_rsp_ready[0];

    //
    clint_cmd_valid = biusplit_o_bus_cmd_valid[1];
    biusplit_o_bus_cmd_ready[1] = clint_cmd_ready & clint_cmd_valid;
    clint_cmd_read = biusplit_o_bus_cmd_read[1];
    clint_cmd_adr = biusplit_o_bus_cmd_adr[1];
    clint_cmd_data = biusplit_o_bus_cmd_data[1];
    biusplit_o_bus_rsp_valid[1] = clint_rsp_valid;
    biusplit_o_bus_rsp_rdata[1] = clint_rsp_rdata;
    clint_rsp_ready = biusplit_o_bus_rsp_ready[1];

}