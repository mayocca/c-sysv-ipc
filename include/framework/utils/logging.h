#ifndef __FRAMEWORK_UTILS_LOGGING_H
#define __FRAMEWORK_UTILS_LOGGING_H

#define log0(format) log_message(__FILE__, __func__, __LINE__, format)
#define log1(format, arg1) log_message(__FILE__, __func__, __LINE__, format, arg1)
#define log2(format, arg1, arg2) log_message(__FILE__, __func__, __LINE__, format, arg1, arg2)
#define log3(format, arg1, arg2, arg3) log_message(__FILE__, __func__, __LINE__, format, arg1, arg2, arg3)
#define log4(format, arg1, arg2, arg3, arg4) log_message(__FILE__, __func__, __LINE__, format, arg1, arg2, arg3, arg4)

void log_message(const char *file, const char *function, int line, const char *format, ...);

#endif
