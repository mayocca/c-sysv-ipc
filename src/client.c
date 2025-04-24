#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/os/env.h"
#include "framework/utils/io.h"
#include "framework/utils/logging.h"
#include "alquicor/utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define CHECK_INTERVAL 3

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

    log0("Waiting for manager to start...");
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
    /* Variables */
    property_t property;
    request_t request;
    FILE *properties_file;
    FILE *requests_file;

    /* Wait for semaphore */
    semaphore_wait(properties_semid);

    /* Read properties from file */
    properties_file = file_open(alquicor_properties_path, "r");
    if (properties_file == NULL)
    {
        log0("[!] Failed to open properties file");
        exit(EXIT_FAILURE);
    }

    log0("Available properties:");

    while (file_read(properties_file, &property, sizeof(property_t), (size_t)1) == 1)
    {
        if (property.reserved == 0)
        {
            log4("-> ID: %d, Name: %s, Square meters: %d, Price: $%d", property.id, property.name, property.square_meters, property_get_price(&property));
        }
        else
        {
            log4("-> (SOLD) ID: %d, Name: %s, Square meters: %d, Price: $%d", property.id, property.name, property.square_meters, property_get_price(&property));
        }
    }

    file_close(properties_file);
    semaphore_signal(properties_semid);

    log0("");
    log0("------------------------------------------------");
    log0("");
    log0("Enter the ID of the property you want to request");

    request.property_id = io_read_int();
    io_clear_buffer();

    log0("Enter your last name");
    io_read_line(request.buyer_last_name, MAX_BUYER_LAST_NAME_LENGTH);

    log2("Request: %d, %s", request.property_id, request.buyer_last_name);

    semaphore_wait(requests_semid);

    requests_file = file_open(alquicor_requests_path, "a");
    if (requests_file == NULL)
    {
        log0("[!] Failed to open requests file");
        exit(EXIT_FAILURE);
    }

    log0("Writing request to file");

    file_write(requests_file, &request, sizeof(request_t), (size_t)1);
    file_close(requests_file);

    semaphore_signal(requests_semid);
}
