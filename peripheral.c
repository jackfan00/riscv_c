#include "peripheral.h"

//this is FAKED peripheral device
void peripheral()
{

    //
    peripheral_cmd_ready = peripheral_cmd_valid & 1;
    peripheral_regcs = peripheral_cmd_valid & peripheral_cmd_ready ? 1 : 0;
    peripheral_regwr = !peripheral_cmd_read;
    peripheral_regwadr = peripheral_cmd_adr;
    peripheral_regradr = peripheral_regcs & (!peripheral_regwr) ? peripheral_cmd_adr : peripheral_regradr_clked;
    peripheral_regwdata = peripheral_cmd_data;
    //
    device_reg = peripheral_regcs & peripheral_regwr ? peripheral_regwdata : device_reg_clked;

    //regrdata
    peripheral_read =   peripheral_regcs     & (!peripheral_regwr) ? 1 : 
                        peripheral_rsp_valid &   peripheral_rsp_ready ? 0 :
                        peripheral_read_clked;

    peripheral_rsp_valid = peripheral_regcs & peripheral_regwr? 1 : peripheral_read_clked;

    //faked
    peripheral_rsp_rdata = device_reg;


}