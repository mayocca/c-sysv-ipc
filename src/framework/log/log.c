#include "log/log.h"
#include <time.h>
#include <string.h>

/* Static variables for logger state */
static FILE *log_output = NULL;
static log_level_t minimum_level = LOG_LEVEL_INFO;

/* Maximum length for timestamp string */
#define TIMESTAMP_MAX_LEN 32

/* Maximum length for a single log message */
#define LOG_MESSAGE_MAX_LEN 1024

/* Maximum length for file path */
#define FILE_PATH_MAX_LEN 256

/* Level strings for output - RFC 5424 names */
static const char *level_strings[] = {
    "EMERG",
    "ALERT",
    "CRIT",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"};

int log_init(FILE *output, log_level_t min_level)
{
    /* Default to stderr if no output specified */
    log_output = output ? output : stderr;

    /* Validate and set minimum level */
    if (min_level < LOG_LEVEL_EMERG || min_level > LOG_LEVEL_DEBUG)
    {
        return -1;
    }
    minimum_level = min_level;

    return 0;
}

const char *log_level_to_string(log_level_t level)
{
    if (level < LOG_LEVEL_EMERG || level > LOG_LEVEL_DEBUG)
    {
        return "UNKNOWN";
    }
    return level_strings[level];
}

int log_message(log_level_t level, const char *file, int line, const char *message)
{
    time_t now;
    struct tm *timeinfo;
    char timestamp[TIMESTAMP_MAX_LEN];
    const char *filename;
    int pos;

    /* Check if we should log this level */
    if (level < minimum_level)
    {
        return 0;
    }

    /* Validate parameters */
    if (!message || !file || !log_output)
    {
        return -1;
    }

    /* Get current time */
    now = time(NULL);
    timeinfo = localtime(&now);
    if (!timeinfo)
    {
        return -1;
    }

    /* Format timestamp */
    if (!strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo))
    {
        return -1;
    }

    /* Get filename from path */
    filename = file;
    for (pos = strlen(file); pos >= 0; pos--)
    {
        if (file[pos] == '/' || file[pos] == '\\')
        {
            filename = &file[pos + 1];
            break;
        }
    }

    /* Write formatted log entry */
    if (fprintf(log_output, "[%s] [%s] %s:%d - %s\n",
                timestamp,
                log_level_to_string(level),
                filename,
                line,
                message) < 0)
    {
        return -1;
    }

    /* Flush to ensure message is written */
    return fflush(log_output);
}

int log_cleanup(void)
{
    /* Only close if not stderr */
    if (log_output && log_output != stderr)
    {
        if (fclose(log_output) != 0)
        {
            return -1;
        }
    }

    log_output = NULL;
    return 0;
}