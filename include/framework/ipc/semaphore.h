#ifndef __FRAMEWORK_IPC_SEMAPHORE_H
#define __FRAMEWORK_IPC_SEMAPHORE_H

#include <sys/types.h>

/**
 * @brief Creates or gets a System V semaphore set
 *
 * @param key IPC key for the semaphore set (must be non-zero)
 * @param exclusive Whether to create the semaphore exclusively
 * @return int Semaphore ID on success, -1 on error
 */
int semaphore_create(key_t key, int exclusive);

/**
 * @brief Initializes a semaphore set
 *
 * @param semid Semaphore set identifier
 * @return int  0 on success, -1 on error
 */
int semaphore_init(int semid);

/**
 * @brief Performs a wait (P) operation on a semaphore
 *
 * @param semid Semaphore set identifier
 * @return int  0 on success, -1 on error
 */
int semaphore_wait(int semid);

/**
 * @brief Performs a signal (V) operation on a semaphore
 *
 * @param semid Semaphore set identifier
 * @return int  0 on success, -1 on error
 */
int semaphore_signal(int semid);

/**
 * @brief Destroys a semaphore set
 *
 * @param semid Semaphore set identifier
 * @return int  0 on success, -1 on error
 */
int semaphore_destroy(int semid);

#endif
