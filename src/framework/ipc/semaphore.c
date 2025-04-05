#include "ipc/semaphore.h"

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int create_semaphore(key_t key, int value)
{
    union semun arg;
    int semid = semget(key, 1, IPC_CREAT | 0664);

    if (semid == -1)
    {
        perror("semget");
        return -1;
    }
    arg.val = value;
    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        perror("semctl");
        return -1;
    }
    return semid;
}

int wait_semaphore(int semid, int semnum)
{
    return 0;
}

int signal_semaphore(int semid, int semnum)
{
    return 0;
}

int destroy_semaphore(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}
