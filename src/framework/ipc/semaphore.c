#include "framework/ipc/semaphore.h"
#include "framework/utils/logging.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>

int semaphore_create(key_t key, int create, int exclusive)
{
    int flags = 0666;

    if (create)
    {
        flags |= IPC_CREAT;
    }

    if (exclusive)
    {
        flags |= IPC_EXCL;
    }

    return semget(key, 1, flags);
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

    return semop(semid, &op, (size_t)1);
}

int semaphore_signal(int semid)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    return semop(semid, &op, (size_t)1);
}

int semaphore_destroy(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}
