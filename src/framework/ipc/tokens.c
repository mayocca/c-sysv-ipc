#include "framework/ipc/tokens.h"

#include <stdio.h>
#include <stdlib.h>

key_t token_create(const char *path)
{
    return ftok(path, PROJECT_ID);
}
