#ifndef SEMAPHORE_H
#define SEMAPHORE_H

int create_semaphore();

int wait_semaphore(int semid, int semnum);

int signal_semaphore(int semid, int semnum);

int destroy_semaphore(int semid);

#endif
