#ifndef PERFCHECK_H
#define PERFCHECK_H
void perfcheck();
void perfcheck_clked();

#include "reg.h"

REG32 ifu_2cyc_counter_clked;
REG32 branch_fail_counter_clked;
REG32 branch_success_counter_clked;
REG32 branchjmp_counter_clked;
REG32 jalr_fail_counter_clked;
REG32 jalr_success_counter_clked;
REG32 lsu2itcm_counter_clked;
REG32 div_rwaw_counter_clked;
REG32 load_rwaw_counter_clked;
REG32 lsu_load_counter_clked;
REG32 dec_stall_counter_clked;
BIT perf_enable_clked;

REG32 ifu_2cyc_counter;
REG32 branch_fail_counter;
REG32 branch_success_counter;
REG32 branchjmp_counter;
REG32 jalr_fail_counter;
REG32 jalr_success_counter;
REG32 lsu2itcm_counter;
REG32 div_rwaw_counter;
REG32 load_rwaw_counter;
REG32 lsu_load_counter;
REG32 dec_stall_counter;
BIT perf_enable;

#endif //PERFCHECK_H
