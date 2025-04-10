#include "ipc/semaphore.h"

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int create_semaphore(key_t key, int value, int flags)
{
    union semun arg;
    int semid = semget(key, 1, flags);

    if (semid == -1)
    {
        return -1;
    }
    arg.val = value;
    if (semctl(semid, 0, SETVAL, arg) == -1)
    {
        return -1;
    }
    return semid;
}

int wait_semaphore(int semid, unsigned short semnum, int flags)
{
    struct sembuf op = {
        .sem_num = semnum,
        .sem_op = -1,
        .sem_flg = flags};

    return semop(semid, &op, 1);
}

int signal_semaphore(int semid, unsigned short semnum, int flags)
{
    struct sembuf op = {
        .sem_num = semnum,
        .sem_op = 1,
        .sem_flg = flags};

    return semop(semid, &op, 1);
}

int destroy_semaphore(int semid)
{
    return semctl(semid, 0, IPC_RMID);
}

int get_semaphore_value(int semid, unsigned short semnum)
{
    return semctl(semid, semnum, GETVAL);
}
