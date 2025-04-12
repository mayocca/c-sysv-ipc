#ifndef __FRAMEWORK_UTILS_LOGGING_H
#define __FRAMEWORK_UTILS_LOGGING_H

#define LOG(message) log_message(message, __FILE__, __func__, __LINE__)

void log_message(const char *message, const char *file, const char *function, int line);

#endif
