#ifndef _LOG_H
#define _LOG_H

#include <stdio.h>

/**
 * @brief Log levels following RFC 5424 severity levels
 */
typedef enum
{
    LOG_LEVEL_EMERG,   /* System is unusable */
    LOG_LEVEL_ALERT,   /* Action must be taken immediately */
    LOG_LEVEL_CRIT,    /* Critical conditions */
    LOG_LEVEL_ERR,     /* Error conditions */
    LOG_LEVEL_WARNING, /* Warning conditions */
    LOG_LEVEL_NOTICE,  /* Normal but significant condition */
    LOG_LEVEL_INFO,    /* Informational messages */
    LOG_LEVEL_DEBUG    /* Debug-level messages */
} log_level_t;

/**
 * @brief Initialize the logging system
 *
 * @param output File to write logs to (NULL for stderr)
 * @param min_level Minimum level to log
 * @return int 0 on success, -1 on error
 */
int log_init(FILE *output, log_level_t min_level);

/**
 * @brief Log a message with the specified level
 *
 * @param level Log level of the message
 * @param file Source file where log was called
 * @param line Line number where log was called
 * @param message Pre-formatted message string
 * @return int 0 on success, -1 on error
 */
int log_message(log_level_t level, const char *file, int line, const char *message);

/**
 * @brief Get the string representation of a log level
 *
 * @param level Log level to convert
 * @return const char* String representation, never NULL
 */
const char *log_level_to_string(log_level_t level);

/**
 * @brief Clean up logging resources
 *
 * @return int 0 on success, -1 on error
 */
int log_cleanup(void);

/* Convenience macros for common log levels */
#define log_emerg(msg) log_message(LOG_LEVEL_EMERG, __FILE__, __LINE__, (msg))
#define log_alert(msg) log_message(LOG_LEVEL_ALERT, __FILE__, __LINE__, (msg))
#define log_crit(msg) log_message(LOG_LEVEL_CRIT, __FILE__, __LINE__, (msg))
#define log_err(msg) log_message(LOG_LEVEL_ERR, __FILE__, __LINE__, (msg))
#define log_warning(msg) log_message(LOG_LEVEL_WARNING, __FILE__, __LINE__, (msg))
#define log_notice(msg) log_message(LOG_LEVEL_NOTICE, __FILE__, __LINE__, (msg))
#define log_info(msg) log_message(LOG_LEVEL_INFO, __FILE__, __LINE__, (msg))
#define log_debug(msg) log_message(LOG_LEVEL_DEBUG, __FILE__, __LINE__, (msg))

#endif
