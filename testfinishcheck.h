#ifndef TESTFINISHCHECK_H
#define TESTFINISHCHECK_H
int testfinishcheck();
void testfinishcheck_clked();

#include "reg.h"

#define HAS_REFERENCEOUT 0
#define PC_WRITE_TOHOST 0x80000086

char * testcase;

REG8 write_tohost_counter_clked;
REG32 teststart_cyclecount_clked;

//
REG8 write_tohost_counter;
REG32 teststart_cyclecount;

#endif //TESTFINISHCHECK_H