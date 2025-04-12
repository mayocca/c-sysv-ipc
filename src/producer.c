#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/os/env.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void setup(void);
void loop(void);

FILE *file;
int semid;

int main(int argc, char *argv[])
{

    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }

    framework_init();

    setup();

    while (1)
    {
        loop();

        sleep(1);
    }

    return EXIT_SUCCESS;
}

void setup(void)
{
    /* Variables */
    char *file_path;
    key_t key;

    /* Get file path from environment */
    file_path = env_get("FILE_PATH", "/tmp/medication.dat");

    /* Create file if it doesn't exist */
    file_open(file_path, "w");

    log1("File path: %s", file_path);

    file = file_open(file_path, "w");
    if (file == NULL)
    {
        log1("Failed to open file: %s", file_path);
        exit(EXIT_FAILURE);
    }

    log0("File opened");

    /* Create semaphore */
    key = token_create(file_path);

    if (key == -1)
    {
        log0("Failed to create token");
        exit(EXIT_FAILURE);
    }

    semid = semaphore_create(key);
    if (semid == -1)
    {
        log0("Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    if (semaphore_init(semid) == -1)
    {
        log0("Failed to initialize semaphore");
        exit(EXIT_FAILURE);
    }

    log0("Semaphore created and initialized");
}

void loop(void)
{
    log0("Producing...");
}
