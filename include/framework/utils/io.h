#ifndef __FRAMEWORK_UTILS_IO_H
#define __FRAMEWORK_UTILS_IO_H

#include <stdio.h>

/**
 * Reads a line from the standard input until a newline character is encountered.
 * The newline character is not included in the returned string.
 *
 * @param buffer The buffer to store the read line.
 * @param size The size of the buffer.
 */
void io_read_line(char *buffer, int size);

/**
 * Reads an integer from the standard input.
 *
 * @return The integer read from the standard input.
 */
int io_read_int(void);

/**
 * Clears the standard input buffer.
 */
void io_clear_buffer(void);

#endif
