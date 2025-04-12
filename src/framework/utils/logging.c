#include "framework/utils/logging.h"

#include <stdio.h>
#include <time.h>
#include <stdarg.h>

void log_message(const char *file, int line, const char *format, ...)
{
    va_list args;
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);

    va_start(args, format);

    printf("[%04d-%02d-%02d %02d:%02d:%02d] [%s:%d] ",
           tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
           tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec, file, line);

    vprintf(format, args);
    printf("\n");

    va_end(args);
}
