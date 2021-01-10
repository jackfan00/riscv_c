#ifndef SIMUART_H
#define SIMUART_H

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>

#include "../reg.h"
REG32 * simuart(key_t mykey, size_t mysize);

REG32 * txuart0_shmptr;
REG32 * rxuart0_shmptr;

#endif //SIMUART_H