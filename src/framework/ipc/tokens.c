#include "framework/ipc/tokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

key_t token_create(const char *path)
{
    key_t key;

    key = ftok(path, PROJECT_ID);
    if (key == -1)
    {
        perror("Failed to create token");
        exit(EXIT_FAILURE);
    }

    return key;
}
