#ifndef _FILES_H
#define _FILES_H

#include <stdio.h>
#include <stddef.h>

/**
 * @brief Open a file
 *
 * @param path Path to the file (must not be NULL)
 * @param mode Mode to open the file (must not be NULL)
 * @return FILE* File descriptor on success, NULL on failure
 */
FILE *open_file(const char *path, const char *mode);

/**
 * @brief Read from a file into a buffer
 *
 * @param file File descriptor (must not be NULL)
 * @param buffer Buffer to store the file contents (must not be NULL)
 * @param size Size of the buffer in bytes
 * @return size_t Number of bytes read on success, 0 on EOF, (size_t)-1 on error
 */
size_t read_file(FILE *file, char *buffer, size_t size);

/**
 * @brief Write a buffer to a file
 *
 * @param file File descriptor (must not be NULL)
 * @param buffer Buffer containing data to write (must not be NULL)
 * @param size Number of bytes to write
 * @return size_t Number of bytes written on success, (size_t)-1 on error
 */
size_t write_file(FILE *file, char *buffer, size_t size);

/**
 * @brief Close a file
 *
 * @param file File descriptor (must not be NULL)
 * @return int 0 on success, EOF on error
 */
int close_file(FILE *file);

#endif
