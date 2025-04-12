#include "framework/os/env.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    char consumer_type;
    char *file_path;

    if (argc != 2 || (*argv[1] != 'A' && *argv[1] != 'B' && *argv[1] != 'C'))
    {
        printf("Usage: %s A|B|C\n", argv[0]);
        return EXIT_FAILURE;
    }

    consumer_type = *argv[1];
    file_path = env_get("FILE_PATH", "/tmp/medication.dat");

    log1("Consumer started: %c", consumer_type);

    log1("File path: %s", file_path);

    return EXIT_SUCCESS;
}
