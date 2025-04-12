#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <sys/types.h>

/**
 * @brief Creates or gets a System V semaphore set
 *
 * @param key     IPC key for the semaphore set (must be non-zero)
 * @param value   Initial value for the semaphore (must be >= 0)
 * @param flags   Creation flags (e.g., IPC_CREAT | IPC_EXCL | 0666)
 * @return int    Semaphore ID on success, -1 on error
 */
int create_semaphore(key_t key, int value, int flags);

/**
 * @brief Performs a wait (P) operation on a semaphore
 *
 * @param semid   Semaphore set identifier
 * @param semnum  Semaphore number in the set (0-based)
 * @param flags   Operation flags (0 for blocking, IPC_NOWAIT for non-blocking)
 * @return int    0 on success, -1 on error
 */
int wait_semaphore(int semid, unsigned short semnum, int flags);

/**
 * @brief Performs a signal (V) operation on a semaphore
 *
 * @param semid   Semaphore set identifier
 * @param semnum  Semaphore number in the set (0-based)
 * @param flags   Operation flags (0 for blocking, IPC_NOWAIT for non-blocking)
 * @return int    0 on success, -1 on error
 */
int signal_semaphore(int semid, unsigned short semnum, int flags);

/**
 * @brief Destroys a semaphore set
 *
 * @param semid   Semaphore set identifier
 * @return int    0 on success, -1 on error
 */
int destroy_semaphore(int semid);

#endif
