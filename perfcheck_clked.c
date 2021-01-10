#include "perfcheck.h"

void perfcheck_clked()
{
    ifu_2cyc_counter_clked = ifu_2cyc_counter;
    branchjmp_counter_clked = branchjmp_counter;
    branch_fail_counter_clked = branch_fail_counter;
    branch_success_counter_clked = branch_success_counter;
    jalr_fail_counter_clked = jalr_fail_counter;
    jalr_success_counter_clked = jalr_success_counter;
    lsu2itcm_counter_clked = lsu2itcm_counter;
    div_rwaw_counter_clked = div_rwaw_counter;
    load_rwaw_counter_clked = load_rwaw_counter;
    lsu_load_counter_clked = lsu_load_counter;
    dec_stall_counter_clked = dec_stall_counter;

    perf_enable_clked = perf_enable;

}