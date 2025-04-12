#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"

#include <stdio.h>
#include <stdlib.h>

key_t token_create(const char *path)
{
    key_t key;

    key = ftok(path, PROJECT_ID);
    if (key == -1)
    {
        log0("Failed to create token");
        exit(EXIT_FAILURE);
    }

    return key;
}
