#include "framework/args/env.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    char *file_path;

    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }

    file_path = env_get("FILE_PATH", "/tmp/medication.dat");

    LOG("Producer started");

    LOG(file_path);

    return EXIT_SUCCESS;
}
