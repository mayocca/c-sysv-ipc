#ifndef TOKENS_H
#define TOKENS_H

#include <sys/types.h>

#define PROJECT_ID 1337

/**
 * Create a token via ftok
 * @return: The token
 */
key_t tok_create(void);

#endif
