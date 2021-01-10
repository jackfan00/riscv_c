#ifndef TESTFINISHCHECK_H
#define TESTFINISHCHECK_H
int testfinishcheck();
void testfinishcheck_clked();

#include "reg.h"
int HAS_REFERENCEOUT;
REG32 PC_WRITE_TOHOST;
//#define COMPLIANCE_TEST
//#define COMPLIANCE_IMC_TEST
//
//#ifdef COMPLIANCE_TEST
//#define PC_WRITE_TOHOST       0x80000040    //compilance rv32i test
//#define HAS_REFERENCEOUT      1
//#else
//#ifdef COMPLIANCE_IMC_TEST
//#define PC_WRITE_TOHOST       0x80000036    //compilance rv32imc test
//#define HAS_REFERENCEOUT      1
//#else
//#define PC_WRITE_TOHOST       0x80000086  //e200 test
//#define HAS_REFERENCEOUT      0
//#endif
//#endif

char * testcase;
char * referenceout;
REG32 signature_startaddr;

REG8 write_tohost_counter_clked;
REG32 teststart_cyclecount_clked;

//
REG8 write_tohost_counter;
REG32 teststart_cyclecount;

#endif //TESTFINISHCHECK_H