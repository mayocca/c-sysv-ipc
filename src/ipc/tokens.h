#ifndef TOKENS_H
#define TOKENS_H

#include <sys/types.h>

/**
 * Create a token via ftok
 * @param pathname: The pathname of the file to create the token from
 * @param proj_id: The project ID to create the token from
 * @return: The token
 */
key_t create_token(const char *pathname, int proj_id);

#endif
