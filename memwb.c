#include "memwb.h"
#include "execu.h"
#include "mul.h"
//#include "memwb_bus.h"
#include "lif.h"

void memwb()
{
    BIT exeres2regw_stall;
    int i;

    //CSR
    memwb_load = exe_load_clked;
    memwb_div = exe_div_clked;
    memwb_dec_ilg = exe_dec_ilg_clked;
    memwb_load_misaligned = lsu_load_misaligned_clked;
    memwb_store_misaligned = lsu_store_misaligned_clked;
    memwb_ecall = exe_aluop_ecall_clked;
    memwb_break = exe_aluop_break_clked;
    memwb_lsu_misaligned_adr = lsu_misaligned_adr_clked;
    memwb_IR = exe_IR_d1_clked;
    memwb_excephappen = memwb_dec_ilg|memwb_load_misaligned|memwb_store_misaligned|memwb_ecall|memwb_break;
    memwb_mret = exe_mret_clked;
    memwb_pc = exe_pc_d1_clked;  //correct pc at this stage
    memwb_ir16 = exe_ir16_d1_clked;
    memwb_validir = exe_validir_d1_clked;
    memwb_bjir = exe_bjir_d1_clked;

    csrreg_adr = exe_csridx_clked;
    csrreg_wen = exe_csr_wen_clked;
    csrreg_ren = exe_csr_ren_clked;
    csrreg_wdata = exe_csr_res_clked;


    //write to REGFILE
    memwb2regfile_cmd_valid = exe_rden_clked & exe_res_valid_clked;
    memwb2regfile_cmd_read =0;
    memwb2regfile_cmd_adr = exe_rdidx_clked;
    memwb2regfile_cmd_data = exe_res_clked;
    memwb2regfile_cmd_rwbyte = 0xf;
    memwb2regfile_rsp_ready =1;
    memwb2regfile_stall = memwb2regfile_cmd_valid & (!memwb2regfile_cmd_ready);
    memwb_stall = memwb2regfile_stall;

    /************
    memwb_wdata = o_memwb_bus_cmd_wdata;
    o_memwb_bus_cmd_ready = memwb_ready;
    memwb_valid = o_memwb_bus_cmd_valid ;
    memwb_id = o_memwb_bus_cmd_id;
    //
    memwb_idx = lifvalid_clked[memwb_id*2] ? lifrdidx_clked[memwb_id*2] : exe_rdidx_clked;
    //normal exe result is low priority to write regs
    //if regw conflicts with other reqs(mul/div/lsu)
    //pipeline will be stalled
    //if (mul/div/lsu) conflicts with others, stall-controll code at execu stage
    exeres2regw_stall = i_memwb_bus_cmd_valid[EXEBUSID] & (!i_memwb_bus_cmd_ready[EXEBUSID]);
    memwb_stall = (memwb_valid & (!memwb_ready)) | exeres2regw_stall;
    */
}
