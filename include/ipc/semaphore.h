#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>

int create_semaphore(key_t key, int value);

int wait_semaphore(int semid, int semnum);

int signal_semaphore(int semid, int semnum);

int destroy_semaphore(int semid);

#endif
