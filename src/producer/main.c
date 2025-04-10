#include "framework/init.h"
#include "log/log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int setup_producer(void)
{
    char msg[256];
    framework_options_t options;

    /* Get default options */
    if (framework_get_default_options(&options) != 0)
    {
        fprintf(stderr, "Failed to get default options\n");
        return -1;
    }

    /* Customize options for producer */
    options.log_file = "producer.log";
    options.log_level = LOG_LEVEL_DEBUG;

    /* Initialize framework */
    if (framework_init_with_options(&options) != 0)
    {
        fprintf(stderr, "Failed to initialize framework\n");
        return -1;
    }

    /* Log producer startup */
    sprintf(msg, "Producer starting up");
    log_info(msg);

    return 0;
}

static int run_producer(void)
{
    char msg[256];

    /* Example producer logic */
    sprintf(msg, "Producer running - ready to generate data");
    log_info(msg);

    /* TODO: Implement actual producer logic */

    return 0;
}

static int cleanup_producer(void)
{
    char msg[256];

    sprintf(msg, "Producer shutting down");
    log_info(msg);

    return framework_cleanup();
}

int main(void)
{
    int status = 0;

    /* Initialize the producer */
    if (setup_producer() != 0)
    {
        return 1;
    }

    /* Run the producer logic */
    status = run_producer();

    /* Clean up */
    if (cleanup_producer() != 0)
    {
        return 1;
    }

    return status;
}
