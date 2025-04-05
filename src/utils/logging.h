#ifndef LOGGING_H
#define LOGGING_H

#include <stdarg.h>
#include <stdio.h>

/**
 * @brief Log levels in order of decreasing severity
 *
 * The log level determines which messages are output:
 * - Only messages with level <= current log level are printed
 * - e.g. if level is WARNING, all messages from EMERGENCY to WARNING are printed
 */
typedef enum
{
    LOG_EMERGENCY, /**< System is unusable */
    LOG_ALERT,     /**< Action must be taken immediately */
    LOG_CRITICAL,  /**< Critical conditions */
    LOG_ERROR,     /**< Error conditions */
    LOG_WARNING,   /**< Warning conditions */
    LOG_NOTICE,    /**< Normal but significant conditions */
    LOG_INFO,      /**< Informational messages */
    LOG_DEBUG,     /**< Debug-level messages */
} LogLevel;

/**
 * @brief Get the current log level threshold
 *
 * @return LogLevel The current log level
 * @thread_safety Thread safe
 */
extern LogLevel get_log_level(void);

/**
 * @brief Set the log level threshold
 *
 * @param level New log level threshold. Messages with level <= threshold are printed
 * @thread_safety Thread safe
 */
extern void set_log_level(LogLevel level);

/**
 * @brief Set the output stream for log messages
 *
 * @param stream File stream to write logs to (e.g. stdout, stderr, or a file)
 * @thread_safety Thread safe
 * @note If stream is NULL, stdout will be used as default
 */
extern void set_log_stream(FILE *stream);

/**
 * @brief Get the current output stream
 *
 * @return FILE* Current output stream (never NULL, defaults to stdout)
 * @thread_safety Thread safe
 */
extern FILE *get_log_stream(void);

/**
 * @brief Log a formatted message with source location
 *
 * @param level Log level of the message
 * @param file Source file where log was called
 * @param line Line number where log was called
 * @param fmt Printf-style format string
 * @param ... Format string arguments
 * @thread_safety Thread safe
 *
 * @note Format string follows printf conventions
 * @note Output format: [TIME][LEVEL][FILE:LINE] message
 */
extern void log_message_fmt(LogLevel level, const char *file, int line, const char *fmt, ...);

/**
 * @brief Internal function to handle va_list arguments
 *
 * @param level Log level of the message
 * @param file Source file where log was called
 * @param line Line number where log was called
 * @param fmt Printf-style format string
 * @param args Variable argument list
 * @thread_safety Thread safe
 *
 * @note This is mainly for internal use - prefer the LOG_* macros
 */
extern void vlog_message_fmt(LogLevel level, const char *file, int line, const char *fmt, va_list args);

// Convenience macros for automatic file and line information
/**
 * @brief Base logging macro - automatically adds file and line information
 * @param level Log level to use
 * @param ... Format string and arguments
 */
#define LOG_MESSAGE(level, ...) log_message_fmt(level, __FILE__, __LINE__, __VA_ARGS__)

/**
 * @brief Log an emergency message (system is unusable)
 * @param ... Format string and arguments
 */
#define LOG_EMERGENCY(...) LOG_MESSAGE(LOG_EMERGENCY, __VA_ARGS__)

/**
 * @brief Log an alert message (immediate action required)
 * @param ... Format string and arguments
 */
#define LOG_ALERT(...) LOG_MESSAGE(LOG_ALERT, __VA_ARGS__)

/**
 * @brief Log a critical message (critical conditions)
 * @param ... Format string and arguments
 */
#define LOG_CRITICAL(...) LOG_MESSAGE(LOG_CRITICAL, __VA_ARGS__)

/**
 * @brief Log an error message (error conditions)
 * @param ... Format string and arguments
 */
#define LOG_ERROR(...) LOG_MESSAGE(LOG_ERROR, __VA_ARGS__)

/**
 * @brief Log a warning message (warning conditions)
 * @param ... Format string and arguments
 */
#define LOG_WARNING(...) LOG_MESSAGE(LOG_WARNING, __VA_ARGS__)

/**
 * @brief Log a notice message (normal but significant conditions)
 * @param ... Format string and arguments
 */
#define LOG_NOTICE(...) LOG_MESSAGE(LOG_NOTICE, __VA_ARGS__)

/**
 * @brief Log an info message (informational)
 * @param ... Format string and arguments
 */
#define LOG_INFO(...) LOG_MESSAGE(LOG_INFO, __VA_ARGS__)

/**
 * @brief Log a debug message (debug-level messages)
 * @param ... Format string and arguments
 */
#define LOG_DEBUG(...) LOG_MESSAGE(LOG_DEBUG, __VA_ARGS__)

#endif
