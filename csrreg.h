#ifndef CSRREG_H
#define CSRREG_H
#include "reg.h"
void csrreg();
void csrreg_clked();

#define MVENDORID 0x0
#define MARCHID 0x0
#define MIMPID 0x1
#define MHARTID 0x0
#define MISA 0x40001105 //imac

REG32 mtval_clked;
REG32 mscratch_clked;
REG32 mtvec_clked;
REG32 mcause_clked;
REG32 mepc_clked;
BIT mstatusmie_clked;
BIT mstatusmpie_clked;
REG32 mie_clked;
BIT meip;
BIT mtip;
BIT msip;
REG32 mcycle_clked;
REG32 mcycleh_clked;
REG32 minstret_clked;
REG32 minstreth_clked;

REG32 mtval;
REG32 mscratch;
REG32 mtvec;
REG32 mcause;
REG32 mepc;
BIT mstatusmie;
BIT mstatusmpie;
REG32 mie;
REG32 csr_rdata;
REG32 mip;
REG32 mcycle;
REG32 mcycleh;
REG32 minstret;
REG32 minstreth;
BIT mie_meie;
BIT mie_mtie;
BIT mie_msie;
BIT csr_inthappen;
REG32 intcause;
REG32 excepcause;
REG32 intpc;
REG32 exceppc;
REG32 real_csr_rdata;
REG32 csrtrappc;
BIT csr_cmd_exception_valid;
BIT csr_cmd_exception_ready;
BIT csr_exception_stall;
BIT csr_exception_flush;

#endif //CSRREG_H