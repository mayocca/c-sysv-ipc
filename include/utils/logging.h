#ifndef LOGGING_H
#define LOGGING_H

typedef enum {
    EMERGENCY,
    ALERT,
    CRITICAL,
    ERROR,
    WARNING,
    NOTICE,
    INFO,
    DEBUG
} LogLevel;

void set_log_level(LogLevel level);
LogLevel get_log_level(void);
void set_log_stream(FILE *stream);
FILE *get_log_stream(void);

void get_current_time(char *buffer, size_t size);
void vlog_message_fmt(LogLevel level, const char *file, int line, const char *fmt, va_list args);
void vlog_message(LogLevel level, const char *file, int line, const char *fmt, ...);
void log_message(LogLevel level, const char *file, int line, const char *fmt, ...);


#endif
