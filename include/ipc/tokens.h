#ifndef TOKENS_H
#define TOKENS_H

#include <sys/types.h>

#define PROJECT_ID 1337

/**
 * @brief Create a token for IPC mechanisms
 *
 * @return key_t Valid token on success, -1 on error
 */
key_t tok_create(void);

#endif
