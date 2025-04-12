#include "framework/ipc/semaphore.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>

int semaphore_create(key_t key)
{
    union semun arg;
    int semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1)
    {
        perror("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    arg.val = 1;
    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("Failed to initialize semaphore");
        exit(EXIT_FAILURE);
    }

    return semid;
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

int semaphore_destroy(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}
