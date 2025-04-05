#include "utils/logging.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
#include <pthread.h>

// Thread-safe log level
static LogLevel log_level = LOG_INFO;
static pthread_mutex_t log_mutex = PTHREAD_MUTEX_INITIALIZER;

// Default to stdout
static FILE *log_stream = NULL;

// Lookup table for log level strings
static const char *const LOG_LEVEL_STRINGS[] = {
    "EMERGENCY",
    "ALERT",
    "CRITICAL",
    "ERROR",
    "WARNING",
    "NOTICE",
    "INFO",
    "DEBUG"};

void set_log_level(LogLevel level)
{
    pthread_mutex_lock(&log_mutex);
    log_level = level;
    pthread_mutex_unlock(&log_mutex);
}

LogLevel get_log_level(void)
{
    LogLevel current;
    pthread_mutex_lock(&log_mutex);
    current = log_level;
    pthread_mutex_unlock(&log_mutex);
    return current;
}

void set_log_stream(FILE *stream)
{
    pthread_mutex_lock(&log_mutex);
    log_stream = stream;
    pthread_mutex_unlock(&log_mutex);
}

FILE *get_log_stream(void)
{
    if (!log_stream)
    {
        return stdout;
    }
    return log_stream;
}

static void get_current_time(char *buffer, size_t size)
{
    time_t now;
    struct tm *timeinfo;

    time(&now);
    timeinfo = localtime(&now);
    strftime(buffer, size, "%Y-%m-%d %H:%M:%S", timeinfo);
}

void vlog_message_fmt(LogLevel level, const char *file, int line, const char *fmt, va_list args)
{
    char timestamp[32];
    FILE *out = get_log_stream();

    pthread_mutex_lock(&log_mutex);

    if (level <= log_level)
    {
        get_current_time(timestamp, sizeof(timestamp));

        // Print header with timestamp, level, file and line
        fprintf(out, "[%s][%s][%s:%d] ",
                timestamp,
                LOG_LEVEL_STRINGS[level],
                file, line);

        // Print actual message
        vfprintf(out, fmt, args);
        fprintf(out, "\n");
        fflush(out);
    }

    pthread_mutex_unlock(&log_mutex);
}

void log_message_fmt(LogLevel level, const char *file, int line, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vlog_message_fmt(level, file, line, fmt, args);
    va_end(args);
}
