#include "framework/utils/logging.h"

#include <stdio.h>
#include <time.h>

void log_message(const char *message, const char *file, const char *function, int line)
{
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);

    printf("[%04d-%02d-%02d %02d:%02d:%02d] [%s:%s:%d] %s\n",
           tm_now->tm_year + 1900, tm_now->tm_mon + 1, tm_now->tm_mday,
           tm_now->tm_hour, tm_now->tm_min, tm_now->tm_sec, file, function, line, message);
}
