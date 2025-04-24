#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/os/env.h"
#include "framework/utils/logging.h"
#include "alquicor/utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define CHECK_INTERVAL 1

void setup(void);
void loop(void);
void cleanup(int signum);

int properties_semid;
int requests_semid;
char *alquicor_properties_path;
char *alquicor_requests_path;

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }

    framework_init();

    log0("================================================");
    log0("Starting client setup");
    log0("================================================");

    setup();

    log0("================================================");
    log0("Starting client loop");
    log0("================================================");

    log0("Waiting for 3 seconds...");
    sleep(3);

    while (1)
    {
        clear_screen();

        loop();

        sleep(CHECK_INTERVAL);
    }

    return EXIT_SUCCESS;
}

void setup(void)
{
    /* Variables */
    key_t properties_key;
    key_t requests_key;

    /* Get file path from environment */
    alquicor_properties_path = env_get("ALQUICOR_PROPERTIES_PATH", DEFAULT_PROPERTIES_FILE_PATH);
    alquicor_requests_path = env_get("ALQUICOR_REQUESTS_PATH", DEFAULT_REQUESTS_FILE_PATH);

    while (file_open(alquicor_properties_path, "r") == NULL || file_open(alquicor_requests_path, "r") == NULL)
    {
        log0("[!] Waiting for files to be created. Run manager first or set ALQUICOR_PROPERTIES_PATH and ALQUICOR_REQUESTS_PATH environment variables.");

        sleep(3);
    }

    /* Create semaphore */
    properties_key = token_create(alquicor_properties_path);
    requests_key = token_create(alquicor_requests_path);

    if (properties_key == -1)
    {
        log0("[!] Failed to create token for properties");
        exit(EXIT_FAILURE);
    }

    if (requests_key == -1)
    {
        log0("[!] Failed to create token for requests");
        exit(EXIT_FAILURE);
    }

    properties_semid = semaphore_create(properties_key, 0, 0);
    requests_semid = semaphore_create(requests_key, 0, 0);

    while (requests_semid == -1)
    {
        log0("[!] Waiting for semaphore to be created. Run manager first or set ALQUICOR_PROPERTIES_PATH and ALQUICOR_REQUESTS_PATH environment variables.");

        sleep(3);

        properties_semid = semaphore_create(properties_key, 0, 0);
        requests_semid = semaphore_create(requests_key, 0, 0);
    }

    signal(SIGINT, cleanup);

    log0("Semaphores created");
}

void cleanup(int signum)
{
    (void)signum;

    log0("================================================");
    log0("<CTRL+C> received, cleaning up...");
    log0("================================================");

    exit(EXIT_SUCCESS);
}

void loop(void)
{
    log0("Client loop");
}
