#include "perfcheck.h"
#include "decode.h"
#include "execu.h"
#include "fetch.h"
#include "regfilemerge.h"
#include "lsubussplit.h"
#include "memwb.h"

void perfcheck()
{
    perf_enable =   dec_csr_ren & (csridx==0xb00) & perf_enable_clked ? 0 : 
                    dec_csr_ren & (csridx==0xb00) ? 1 : 
                    perf_enable_clked;
    branchjmp_counter   = branchjmp             & perf_enable_clked ? branchjmp_counter_clked+1 : branchjmp_counter_clked;
    ifu_2cyc_counter    = pc_keep_clked         & perf_enable_clked ? ifu_2cyc_counter_clked+1 : ifu_2cyc_counter_clked;
    branch_fail_counter = exe_branch_pdict_fail & perf_enable_clked ? branch_fail_counter_clked+1 : branch_fail_counter_clked;
    branch_success_counter = exe_branch_pdict_success & perf_enable_clked ? branch_success_counter_clked+1 : branch_success_counter_clked;
    jalr_fail_counter   = exe_jalr_pdict_fail   & perf_enable_clked ? jalr_fail_counter_clked+1 : jalr_fail_counter_clked;
    jalr_success_counter   = dec_jalr_pdict_success   & perf_enable_clked ? jalr_success_counter_clked+1 : jalr_success_counter_clked;
    lsu2itcm_counter    = lsu2itcm_cmd_valid    & perf_enable_clked ? lsu2itcm_counter_clked+1 : lsu2itcm_counter_clked;

    div_rwaw_counter = ( (dec_rwaw_lifdiv_rs1  & (!regfile_wrdiv )) |         
                         (dec_rwaw_lifdiv_rs2  & (!regfile_wrdiv )) |         
                         (dec_rwaw_lifdiv_rd   & (!regfile_wrdiv ))   )  & perf_enable_clked ? div_rwaw_counter_clked+1 : div_rwaw_counter_clked;

    lsu_load_counter = lsu_cmd_valid & perf_enable_clked ? lsu_load_counter_clked+1 : lsu_load_counter_clked;
    load_rwaw_counter = ( (dec_rwaw_lifload_rs1  & (!regfile_wrload )) |         
                          (dec_rwaw_lifload_rs2  & (!regfile_wrload )) |         
                          (dec_rwaw_lifload_rd   & (!regfile_wrload ))   )  & perf_enable_clked ? load_rwaw_counter_clked+1 : load_rwaw_counter_clked;
    dec_stall_counter = dec_stall & perf_enable_clked ? dec_stall_counter_clked+1 : dec_stall_counter_clked;
}