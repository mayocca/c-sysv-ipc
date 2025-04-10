#ifndef _FRAMEWORK_INIT_H
#define _FRAMEWORK_INIT_H

/**
 * @brief Framework initialization options
 */
typedef struct
{
    /* Logging options */
    const char *log_file; /* Path to log file (NULL for stderr) */
    int log_level;        /* Minimum log level to record */

    /* IPC options */
    int ipc_key; /* Base key for IPC mechanisms */

    /* File system options */
    const char *work_dir; /* Working directory (NULL for current) */
} framework_options_t;

/**
 * @brief Initialize the framework with default options
 *
 * Default configuration:
 * - Logging to stderr
 * - Log level: INFO
 * - IPC key: auto-generated
 * - Work dir: current directory
 *
 * @return int 0 on success, -1 on error
 */
int framework_init(void);

/**
 * @brief Initialize the framework with custom options
 *
 * @param options Initialization options (must not be NULL)
 * @return int 0 on success, -1 on error
 */
int framework_init_with_options(const framework_options_t *options);

/**
 * @brief Clean up framework resources
 *
 * @return int 0 on success, -1 on error
 */
int framework_cleanup(void);

/**
 * @brief Get default framework options
 *
 * @param options Options structure to fill (must not be NULL)
 * @return int 0 on success, -1 on error
 */
int framework_get_default_options(framework_options_t *options);

#endif
