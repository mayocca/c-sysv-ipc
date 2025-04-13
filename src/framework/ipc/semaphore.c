#include "framework/ipc/semaphore.h"
#include "framework/utils/logging.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>

int semaphore_create(key_t key)
{
    return semget(key, 1, IPC_CREAT | 0666);
}

int semaphore_init(int semid)
{
    return semctl(semid, 0, SETVAL, 1);
}

int semaphore_wait(int semid)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    return semop(semid, &op, 1);
}

int semaphore_signal(int semid)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    return semop(semid, &op, 1);
}
