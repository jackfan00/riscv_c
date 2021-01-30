#include "extbussplit.h"
#include "ext_write_coderam.h"

void extbussplit()
{
    int i;

    //it is for 3 target case, 
    //if more targets, should assign value to SPLITTARGETNUM-1 index
    extsplit_TARGETBASE[0] = 0x80; //itcm
    extsplit_TARGETBASE[1] = 0x90; //dtcm

    //ext come from execu
    extsplit_i_bus_cmd_valid = ext_cmd_valid;
    ext_cmd_ready = extsplit_i_bus_cmd_ready;
    extsplit_i_bus_cmd_read = ext_cmd_read;
    extsplit_i_bus_cmd_adr = ext_cmd_addr;
    extsplit_i_bus_cmd_data = ext_cmd_wdata;
    extsplit_i_bus_cmd_rwbyte = ext_cmd_rwbyte;
    ext_rsp_read  = extsplit_i_bus_rsp_read;
    ext_rsp_valid = extsplit_i_bus_rsp_valid;
    ext_rsp_rdata = extsplit_i_bus_rsp_rdata;
    extsplit_i_bus_rsp_ready = ext_rsp_ready;
    ext_rsp_rden = extsplit_i_bus_rsp_rden;
    ext_rsp_regidx = extsplit_i_bus_rsp_regidx;

    //
    //dont accept command if fifo is full
    real_extsplit_i_bus_cmd_valid = !exttransacFIFOfull & extsplit_i_bus_cmd_valid;
    //find matching base address except last extsplit_o_bus_cmd_valid
    for (i=0;i<EXTSPLITTARGETNUM-1;i++)
    {
        extsplit_o_bus_cmd_valid[i] = (extsplit_i_bus_cmd_adr>>24)==extsplit_TARGETBASE[i] ? real_extsplit_i_bus_cmd_valid : 0;
        extsplit_o_bus_cmd_read[i] = extsplit_o_bus_cmd_valid[i] ? extsplit_i_bus_cmd_read : 0;
        extsplit_o_bus_cmd_adr[i] = extsplit_o_bus_cmd_valid[i] ? extsplit_i_bus_cmd_adr : 0;
        extsplit_o_bus_cmd_data[i] = extsplit_o_bus_cmd_valid[i] ? extsplit_i_bus_cmd_data : 0;
        extsplit_o_bus_cmd_rwbyte[i] = extsplit_o_bus_cmd_valid[i] ? extsplit_i_bus_cmd_rwbyte : 0;
    }
    //
    //check all previous index extsplit_o_bus_cmd_valid
    extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1]=0;
    for (i=0;i<EXTSPLITTARGETNUM-1;i++)
    {
        extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] = extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1]|extsplit_o_bus_cmd_valid[i];
    }
    //if all previous index dont match, last one target is selected
    extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] = (!extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1]) & real_extsplit_i_bus_cmd_valid;
    extsplit_o_bus_cmd_read[EXTSPLITTARGETNUM-1] = extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] ? extsplit_i_bus_cmd_read : 0;
    extsplit_o_bus_cmd_adr[EXTSPLITTARGETNUM-1]  = extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] ? extsplit_i_bus_cmd_adr : 0;
    extsplit_o_bus_cmd_data[EXTSPLITTARGETNUM-1] = extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] ? extsplit_i_bus_cmd_data : 0;
    extsplit_o_bus_cmd_rwbyte[EXTSPLITTARGETNUM-1] = extsplit_o_bus_cmd_valid[EXTSPLITTARGETNUM-1] ? extsplit_i_bus_cmd_rwbyte : 0;

    //
    exttransacFIFO_wen = extsplit_i_bus_cmd_ready & extsplit_i_bus_cmd_valid;// & extsplit_i_bus_cmd_read;
    exttransacFIFO_wid=0;
    for (i=0;i<EXTSPLITTARGETNUM;i++)
    {
    //    exttransacFIFO_wen =  exttransacFIFO_wen | (extsplit_o_bus_cmd_valid[i] & extsplit_o_bus_cmd_ready[i]);
    //    exttransacFIFO_wid =  exttransacFIFO_wid | ((extsplit_o_bus_cmd_valid[i] & extsplit_o_bus_cmd_ready[i]) ? i : 0);
        exttransacFIFO_wid = exttransacFIFO_wid | (extsplit_o_bus_cmd_valid[i] ? i : 0);
    }
    // accept command and write id into exttransacFIFO                       
    //extsplit_i_bus_cmd_ready = exttransacFIFO_wen;
    exttransacFIFO = exttransacFIFO_wen ? exttransacFIFO_wid : exttransacFIFO_clked[exttransacFIFO_widx_clked];
    nxtwrapped_exttransacFIFO_widx = ((exttransacFIFO_widx_clked==(EXTSPLIFIFODEPTH-1)) ? 0 :  exttransacFIFO_widx_clked+1);
    exttransacFIFO_widx = exttransacFIFO_wen ? nxtwrapped_exttransacFIFO_widx : 
                            exttransacFIFO_widx_clked;
    //store regfile info
    extregfileidxFIFO  = exttransacFIFO_wen ? ext_cmd_regidx : extregfileidxFIFO_clked[exttransacFIFO_widx_clked];
    extregfilerdenFIFO = exttransacFIFO_wen ? ext_cmd_rden : extregfilerdenFIFO_clked[exttransacFIFO_widx_clked];

    //fifo full condition : if next fifo write reach read-idx
    exttransacFIFOfull = (nxtwrapped_exttransacFIFO_widx==exttransacFIFO_ridx_clked);


    //fifo empty definition : if current write-idx equal to current read-idx
    exttransacFIFOempty = (exttransacFIFO_widx_clked==exttransacFIFO_ridx_clked);
    exttransacFIFO_rid =extsplit_i_bus_cmd_valid & (!extsplit_i_bus_cmd_read) & exttransacFIFOempty ? exttransacFIFO_wid : //for write bypass 
                        //exttransacFIFOempty ? exttransacFIFO_wid : 
                        exttransacFIFO_clked[exttransacFIFO_ridx_clked];

    //addition info
    extsplit_i_bus_rsp_regidx= extsplit_i_bus_cmd_valid & (!extsplit_i_bus_cmd_read) & exttransacFIFOempty ? ext_cmd_regidx : extregfileidxFIFO_clked[exttransacFIFO_ridx_clked];
    extsplit_i_bus_rsp_rden  = extsplit_i_bus_cmd_valid & (!extsplit_i_bus_cmd_read) & exttransacFIFOempty ? ext_cmd_rden   : extregfilerdenFIFO_clked[exttransacFIFO_ridx_clked];

    //
    extsplit_i_bus_rsp_read =0;
    extsplit_i_bus_rsp_valid=0;
    extsplit_i_bus_rsp_rdata=0;
    for (i=0;i<EXTSPLITTARGETNUM;i++)
    {
        //extsplit_i_bus_rsp_regidx  = extsplit_i_bus_rsp_regidx  | (exttransacFIFO_rid==i ? extsplit_o_bus_rsp_regidx[i]  : 0) ;
        //extsplit_i_bus_rsp_rden  = extsplit_i_bus_rsp_rden  | (exttransacFIFO_rid==i ? extsplit_o_bus_rsp_rden[i]  : 0) ;
        extsplit_i_bus_rsp_read  = extsplit_i_bus_rsp_read  | (exttransacFIFO_rid==i ? extsplit_o_bus_rsp_read[i]  : 0) ;
        extsplit_i_bus_rsp_valid = extsplit_i_bus_rsp_valid | (exttransacFIFO_rid==i ? extsplit_o_bus_rsp_valid[i] : 0) ;
        extsplit_i_bus_rsp_rdata = extsplit_i_bus_rsp_rdata | (exttransacFIFO_rid==i ? extsplit_o_bus_rsp_rdata[i] : 0) ;
        extsplit_o_bus_rsp_ready[i] = exttransacFIFO_rid==i ? extsplit_i_bus_rsp_ready : 0;
    }

    //rsp accept and move exttransacFIFO_ridx to next item
    exttransacFIFO_ren = extsplit_i_bus_rsp_valid & extsplit_i_bus_rsp_ready ;//& extsplit_i_bus_rsp_read &
                            //(extsplit_i_bus_cmd_valid?extsplit_i_bus_cmd_read:1) ; //eliminate write case

    exttransacFIFO_ridx = exttransacFIFO_ren ? ((exttransacFIFO_ridx_clked==(EXTSPLIFIFODEPTH-1)) ? 0 :  exttransacFIFO_ridx_clked+1) : 
                            exttransacFIFO_ridx_clked;


    //
    ext2biu_cmd_valid = extsplit_o_bus_cmd_valid[2];
    extsplit_o_bus_cmd_ready[2] = ext2biu_cmd_ready & ext2biu_cmd_valid;
    ext2biu_cmd_read = extsplit_o_bus_cmd_read[2];
    ext2biu_cmd_adr = extsplit_o_bus_cmd_adr[2];
    ext2biu_cmd_data = extsplit_o_bus_cmd_data[2];
    ext2biu_cmd_rwbyte = extsplit_o_bus_cmd_rwbyte[2];
    extsplit_o_bus_rsp_read[2] = ext2biu_rsp_read;
    extsplit_o_bus_rsp_valid[2] = ext2biu_rsp_valid;
    extsplit_o_bus_rsp_rdata[2] = ext2biu_rsp_rdata;
    ext2biu_rsp_ready = extsplit_o_bus_rsp_ready[2];

    //
    ext2dtcm_cmd_valid = extsplit_o_bus_cmd_valid[1];
    extsplit_o_bus_cmd_ready[1] = ext2dtcm_cmd_ready & ext2dtcm_cmd_valid;
    ext2dtcm_cmd_read = extsplit_o_bus_cmd_read[1];
    ext2dtcm_cmd_adr = extsplit_o_bus_cmd_adr[1];
    ext2dtcm_cmd_data = extsplit_o_bus_cmd_data[1];
    ext2dtcm_cmd_rwbyte = extsplit_o_bus_cmd_rwbyte[1];
    extsplit_o_bus_rsp_read[1] = ext2dtcm_rsp_read;
    extsplit_o_bus_rsp_valid[1] = ext2dtcm_rsp_valid;
    extsplit_o_bus_rsp_rdata[1] = ext2dtcm_rsp_rdata;
    ext2dtcm_rsp_ready = extsplit_o_bus_rsp_ready[1];

    //
    ext2itcm_cmd_valid = extsplit_o_bus_cmd_valid[0];
    extsplit_o_bus_cmd_ready[0] = ext2itcm_cmd_ready & ext2itcm_cmd_valid;
    ext2itcm_cmd_read = extsplit_o_bus_cmd_read[0];
    ext2itcm_cmd_adr = extsplit_o_bus_cmd_adr[0];
    ext2itcm_cmd_data = extsplit_o_bus_cmd_data[0];
    ext2itcm_cmd_rwbyte = extsplit_o_bus_cmd_rwbyte[0];
    extsplit_o_bus_rsp_read[0] = ext2itcm_rsp_read;
    extsplit_o_bus_rsp_valid[0] = ext2itcm_rsp_valid;
    extsplit_o_bus_rsp_rdata[0] = ext2itcm_rsp_rdata;
    ext2itcm_rsp_ready = extsplit_o_bus_rsp_ready[0];

    //
    extsplit_i_bus_cmd_ready = extsplit_o_bus_cmd_ready[0]|extsplit_o_bus_cmd_ready[1]|extsplit_o_bus_cmd_ready[2];

}