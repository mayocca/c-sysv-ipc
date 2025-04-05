#include "semaphore.h"
#include "../utils/logging.h"

#include <sys/ipc.h>
#include <sys/sem.h>

int create_semaphore(key_t key, int value)
{
    int semid = semget(key, 1, IPC_CREAT | 0664);
    if (semid == -1)
    {
        log_error("semget");
        return -1;
    }
    union semun arg;
    arg.val = value;
    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        log_error("semctl");
        return -1;
    }
    return semid;
}

int wait_semaphore(int semid, int semnum)
{
    struct sembuf op;
}

int signal_semaphore(int semid, int semnum)
{
    struct sembuf op;
}

int destroy_semaphore(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}