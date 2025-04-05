#include "ipc/tokens.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>

key_t tok_create(void)
{
    key_t key;

    key = ftok("/bin/ls", PROJECT_ID);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    return key;
}
