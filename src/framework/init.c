#include "framework/init.h"
#include "log/log.h"
#include "ipc/tokens.h"
#include <stdlib.h>
#include <unistd.h>

/* Framework state */
static int is_initialized = 0;

/* Default options */
static const framework_options_t default_options = {
    .log_file = NULL, /* stderr */
    .log_level = LOG_LEVEL_INFO,
    .ipc_key = 0,    /* Will be auto-generated */
    .work_dir = NULL /* Current directory */
};

int framework_get_default_options(framework_options_t *options)
{
    if (!options)
    {
        return -1;
    }

    *options = default_options;
    return 0;
}

static int init_logging(const framework_options_t *options)
{
    FILE *log_file = NULL;

    /* Open log file if specified */
    if (options->log_file)
    {
        log_file = fopen(options->log_file, "a");
        if (!log_file)
        {
            return -1;
        }
    }

    /* Initialize logging subsystem */
    if (log_init(log_file, options->log_level) != 0)
    {
        if (log_file)
        {
            fclose(log_file);
        }
        return -1;
    }

    return 0;
}

static int init_working_directory(const framework_options_t *options)
{
    /* Change working directory if specified */
    if (options->work_dir)
    {
        if (chdir(options->work_dir) != 0)
        {
            log_err("Failed to change working directory");
            return -1;
        }
    }

    return 0;
}

static int init_ipc(const framework_options_t *options)
{
    key_t key;

    /* Generate IPC key if not provided */
    if (options->ipc_key == 0)
    {
        key = tok_create();
        if (key == -1)
        {
            log_err("Failed to generate IPC key");
            return -1;
        }
    }

    return 0;
}

int framework_init(void)
{
    framework_options_t options;

    framework_get_default_options(&options);
    return framework_init_with_options(&options);
}

int framework_init_with_options(const framework_options_t *options)
{
    char cwd[256];
    const framework_options_t *opts;

    /* Prevent double initialization */
    if (is_initialized)
    {
        return -1;
    }

    /* Use default options if none provided */
    opts = options ? options : &default_options;

    /* Initialize components in order */
    if (init_logging(opts) != 0)
    {
        return -1;
    }

    if (init_working_directory(opts) != 0)
    {
        log_cleanup();
        return -1;
    }

    if (init_ipc(opts) != 0)
    {
        log_cleanup();
        return -1;
    }

    /* Log successful initialization */
    if (getcwd(cwd, sizeof(cwd)))
    {
        log_info("Framework initialized successfully");
        log_debug("Working directory: %s", cwd);
    }

    is_initialized = 1;
    return 0;
}

int framework_cleanup(void)
{
    if (!is_initialized)
    {
        return -1;
    }

    /* Clean up in reverse order of initialization */
    log_info("Framework shutting down");

    /* Add other cleanup here as components are added */

    log_cleanup();
    is_initialized = 0;

    return 0;
}