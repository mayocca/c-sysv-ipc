#ifndef TOKENS_H
#define TOKENS_H

#include <sys/types.h>

#define PROJECT_ID 1337

/**
 * @brief Create a token for IPC mechanisms
 *
 * @param path Path to the file used to create the token
 * @return key_t Valid token on success, -1 on error
 */
key_t tok_create(const char *path);

#endif
