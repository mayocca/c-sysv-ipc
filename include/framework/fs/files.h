#ifndef __FRAMEWORK_FS_FILES_H
#define __FRAMEWORK_FS_FILES_H

#include <stdio.h>

/**
 * @brief Open a file
 *
 * @param path Path to the file (must not be NULL)
 * @param mode Mode to open the file (must not be NULL)
 * @return FILE* File descriptor on success, NULL on failure
 */
FILE *file_open(const char *path, const char *mode);

/**
 * @brief Read from a file into a buffer
 *
 * @param file File descriptor (must not be NULL)
 * @param buffer Buffer to store the file contents (must not be NULL)
 * @param size Size of each item in bytes
 * @param items Number of items to read
 * @return size_t Number of bytes read on success, 0 on error
 */
size_t file_read(FILE *file, void *buffer, size_t size, size_t items);

/**
 * @brief Write a buffer to a file
 *
 * @param file File descriptor (must not be NULL)
 * @param buffer Buffer containing data to write (must not be NULL)
 * @param size Size of each item in bytes
 * @param items Number of items to write
 * @return size_t Number of bytes written on success, 0 on error
 */
size_t file_write(FILE *file, const void *buffer, size_t size, size_t items);

/**
 * @brief Close a file
 *
 * @param file File descriptor (must not be NULL)
 * @return int 0 on success, EOF on error
 */
int file_close(FILE *file);

#endif
