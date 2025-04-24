#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/os/env.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/utils/logging.h"
#include "framework/utils/rand.h"
#include "restaurant/utils.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define PRODUCE_INTERVAL 1

void setup(void);
void loop(void);
void cleanup(int signum);

void produce_random_order(order_t *order);
void write_order_to_file(order_t *order);

int semid;
char *file_path;

int main(int argc, char *argv[])
{

    if (argc != 1)
    {
        printf("Usage: %s\n", argv[0]);
        return EXIT_FAILURE;
    }

    framework_init();

    log0("================================================");
    log0("Producer setup");
    log0("================================================");

    setup();

    log0("================================================");
    log0("Producer loop");
    log0("================================================");

    log0("Waiting for 3 seconds...");
    sleep(3);

    while (1)
    {
        loop();

        sleep(PRODUCE_INTERVAL);
    }

    return EXIT_SUCCESS;
}

void setup(void)
{
    /* Variables */
    key_t key;

    /* Get file path from environment */
    file_path = env_get("FILE_PATH", DEFAULT_FILE_PATH);

    /* Create file if it doesn't exist */
    if (file_open(file_path, "w") == NULL)
    {
        log0("[!] Failed to open file");
        exit(EXIT_FAILURE);
    }

    log1("File path: %s", file_path);

    /* Create semaphore */
    key = token_create(file_path);

    if (key == -1)
    {
        log0("[!] Failed to create token");
        exit(EXIT_FAILURE);
    }

    semid = semaphore_create(key, 1, 1);
    if (semid == -1)
    {
        log0("[!] Failed to create semaphore");
        exit(EXIT_FAILURE);
    }

    if (semaphore_init(semid) == -1)
    {
        log0("[!] Failed to initialize semaphore");
        exit(EXIT_FAILURE);
    }

    signal(SIGINT, cleanup);

    log0("Semaphore created and initialized");
}

void cleanup(int signum)
{
    (void)signum;

    log0("================================================");
    log0("<CTRL+C> received, cleaning up...");
    log0("================================================");

    semaphore_destroy(semid);

    log0("Semaphore destroyed");

    exit(EXIT_SUCCESS);
}

void loop(void)
{
    order_t *order = malloc(sizeof(order_t));

    /* Produce orders */
    produce_random_order(order);

    log3("Produced order: (%c) %s %s", menu_type_to_char(order->type), menu_type_description(order->type), order->wants_dessert ? "con postre" : "sin postre");

    /* Write order to file */
    write_order_to_file(order);

    /* Free order */
    free(order);
}

void produce_random_order(order_t *order)
{
    order->type = (menu_type_t)(rand_int(0, MENU_TYPE_COUNT));
    order->wants_dessert = (rand_int(0, 100) < 50);
}

void write_order_to_file(order_t *order)
{
    FILE *file;

    /* Wait for semaphore */
    semaphore_wait(semid);

    file = file_open(file_path, "a");
    if (file == NULL)
    {
        log0("[!] Failed to open file");
        exit(EXIT_FAILURE);
    }

    file_write(file, order, sizeof(order_t), (size_t)1);
    file_close(file);

    /* Signal semaphore */
    semaphore_signal(semid);
}
