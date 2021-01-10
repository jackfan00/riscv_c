#include "simuart.h"


REG32 * simuart(key_t mykey, size_t mysize)
{
    int shmid;
    REG32 *shmptr;

    if ((shmid=shmget(mykey, mysize, IPC_CREAT|0666))==-1){
        printf("simuart shmget failed\n");
        exit(1);
    }
        printf("simuart shmid=%d \n", shmid);

    if ((shmptr=shmat(shmid, (const void *)0, 0))==(void *)-1){
        perror("simuart shmat failed\n");
        exit(1);
    }

    //initialize
    *shmptr =0;
    return(shmptr);

}