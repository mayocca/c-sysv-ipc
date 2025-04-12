#include "framework/ipc/semaphore.h"

#include <stdlib.h>
#include <sys/sem.h>

int create_semaphore(key_t key)
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

int wait_semaphore(int semid)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = -1;
    op.sem_flg = 0;

    return semop(semid, &op, 1);
}

int signal_semaphore(int semid)
{
    struct sembuf op;

    op.sem_num = 0;
    op.sem_op = 1;
    op.sem_flg = 0;

    return semop(semid, &op, 1);
}

int destroy_semaphore(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}
