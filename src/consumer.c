#include "framework/foundation/init.h"
#include "framework/fs/files.h"
#include "framework/ipc/semaphore.h"
#include "framework/ipc/tokens.h"
#include "framework/os/env.h"
#include "framework/utils/logging.h"
#include "restaurant/utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define CHECK_INTERVAL 1

void setup(void);
void loop(void);

int semid;
char *file_path;
menu_type_t menu_type;

int main(int argc, char *argv[])
{
    if (argc != 2 || (*argv[1] != 'A' && *argv[1] != 'B' && *argv[1] != 'C'))
    {
        printf("Usage: %s A|B|C\n", argv[0]);
        return EXIT_FAILURE;
    }

    menu_type = menu_type_from_char(*argv[1]);
    file_path = env_get("FILE_PATH", "/tmp/menu.dat");

    framework_init();

    log0("================================================");
    log0("Consumer setup");
    log0("================================================");

    setup();

    log0("================================================");
    log0("Consumer loop");
    log0("================================================");

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
    key_t key;

    /* Get file path from environment */
    file_path = env_get("FILE_PATH", "/tmp/menu.dat");

    while (file_open(file_path, "r") == NULL)
    {
        log0("Waiting for file to be created. Run producer first or set FILE_PATH environment variable.");

        sleep(3);
    }

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
    FILE *file;
    order_t *order = malloc(sizeof(order_t));
    int order_count = 0, dessert_count = 0, total_price;

    log1("Checking for orders of type %c", menu_type);

    /* Wait for semaphore */
    semaphore_wait(semid);

    /* Read order from file */
    file = file_open(file_path, "r");
    if (file == NULL)
    {
        log0("Failed to open file");
        exit(EXIT_FAILURE);
    }

    while (file_read(file, order, sizeof(order_t), 1) == 1)
    {
        if (order->type == menu_type)
        {
            order_count++;

            if (order->wants_dessert)
            {
                dessert_count++;
            }
        }
    }

    file_close(file);

    /* Signal semaphore */
    semaphore_signal(semid);

    /* Free order */
    free(order);

    total_price = order_count * menu_type_price(menu_type) + dessert_count * DESSERT_PRICE;

    log4("Total for type %c: $%d (orders: %d, desserts: %d)", menu_type, total_price, order_count, dessert_count);
}
