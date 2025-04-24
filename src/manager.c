#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/os/env.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"
#include "framework/utils/rand.h"
#include "alquicor/utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define CHECK_INTERVAL 1

void setup(void);
void loop(void);
void cleanup(int signum);
void seed_properties(void);
property_t *get_property_by_id(int id);
void set_property_reserved(int id, int reserved);

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
    log0("Manager setup");
    log0("================================================");

    setup();

    log0("================================================");
    log0("Manager loop");
    log0("================================================");

    log0("Waiting for 3 seconds...");
    sleep(3);

    while (1)
    {
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

    /* Create file if it doesn't exist */
    if (file_open(alquicor_properties_path, "w") == NULL)
    {
        log0("[!] Failed to open properties file");
        exit(EXIT_FAILURE);
    }

    if (file_open(alquicor_requests_path, "w") == NULL)
    {
        log0("[!] Failed to open requests file");
        exit(EXIT_FAILURE);
    }

    log1("Alquicor properties path: %s", alquicor_properties_path);
    log1("Alquicor requests path: %s", alquicor_requests_path);

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

    properties_semid = semaphore_create(properties_key, 1, 1);
    if (properties_semid == -1)
    {
        log0("[!] Failed to create semaphore for properties");
        exit(EXIT_FAILURE);
    }

    if (semaphore_init(properties_semid) == -1)
    {
        log0("[!] Failed to initialize semaphore for properties");
        exit(EXIT_FAILURE);
    }

    requests_semid = semaphore_create(requests_key, 1, 1);
    if (requests_semid == -1)
    {
        log0("[!] Failed to create semaphore for requests");
        exit(EXIT_FAILURE);
    }

    if (semaphore_init(requests_semid) == -1)
    {
        log0("[!] Failed to initialize semaphore for requests");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, cleanup);
    log0("Semaphores created and initialized");

    seed_properties();
    log0("Properties seeded");

    log0("Manager setup complete");
}

void cleanup(int signum)
{
    (void)signum;

    log0("================================================");
    log0("<CTRL+C> received, cleaning up...");
    log0("================================================");

    semaphore_destroy(properties_semid);
    log0("Properties semaphore destroyed");
    semaphore_destroy(requests_semid);
    log0("Requests semaphore destroyed");

    exit(EXIT_SUCCESS);
}

void loop(void)
{
    int request_count = 0;
    request_t request;
    property_t *property;
    FILE *requests_file;

    semaphore_wait(requests_semid);
    semaphore_wait(properties_semid);

    /* Read requests from file */
    requests_file = file_open(alquicor_requests_path, "r");
    if (requests_file == NULL)
    {
        log0("[!] Failed to open requests file");
        exit(EXIT_FAILURE);
    }

    while (file_read(requests_file, &request, sizeof(request_t), (size_t)1) == 1)
    {
        property = get_property_by_id(request.property_id);
        if (property != NULL && property->reserved == 0)
        {
            log2("Property %s requested by %s. Marking as reserved", property->name, request.buyer_last_name);
            set_property_reserved(property->id, 1);
            request_count++;
        }
        else
        {
            log1("Property %s already reserved, skipping", property->name);
        }
    }

    file_close(requests_file);
    semaphore_signal(requests_semid);
    semaphore_signal(properties_semid);

    log1("Requests processed: %d", request_count);
}

property_t *get_property_by_id(int id)
{
    property_t property;
    property_t *found_property = NULL;
    FILE *properties_file;

    /* Wait for semaphore */
    semaphore_wait(properties_semid);

    properties_file = file_open(alquicor_properties_path, "r");
    if (properties_file == NULL)
    {
        log0("[!] Failed to open properties file");
        exit(EXIT_FAILURE);
    }

    while (file_read(properties_file, &property, sizeof(property_t), (size_t)1) == 1)
    {
        if (property.id == id)
        {
            found_property = malloc(sizeof(property_t));
            memcpy(found_property, &property, sizeof(property_t));

            break;
        }
    }

    file_close(properties_file);
    semaphore_signal(properties_semid);

    return found_property;
}

void set_property_reserved(int id, int reserved)
{
    property_t property;
    FILE *properties_file;

    properties_file = file_open(alquicor_properties_path, "r+");
    if (properties_file == NULL)
    {
        log0("[!] Failed to open properties file");
        exit(EXIT_FAILURE);
    }

    while (file_read(properties_file, &property, sizeof(property_t), (size_t)1) == 1)
    {
        if (property.id == id)
        {
            property.reserved = reserved;
            break;
        }
    }

    file_write(properties_file, &property, sizeof(property_t), (size_t)1);
    file_close(properties_file);
}

/* Seeds 4 properties */
void seed_properties(void)
{
    property_t properties[4];
    FILE *properties_file;
    int i = 0;
    char *property_name;

    semaphore_wait(properties_semid);

    properties_file = file_open(alquicor_properties_path, "w");
    if (properties_file == NULL)
    {
        log0("[!] Failed to open properties file");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < 4; i++)
    {
        property_name = malloc(MAX_PROPERTY_NAME_LENGTH);
        memset(property_name, 0, MAX_PROPERTY_NAME_LENGTH);
        sprintf(property_name, "Property %d", i + 1);

        properties[i].id = i;
        properties[i].reserved = 0;
        properties[i].square_meters = rand_int(20, 100);
        memcpy(properties[i].name, property_name, MAX_PROPERTY_NAME_LENGTH);
    }

    file_write(properties_file, properties, sizeof(property_t), 4);
    file_close(properties_file);

    semaphore_signal(properties_semid);
}
