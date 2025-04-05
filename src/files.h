#ifndef _FILES_H
#define _FILES_H

/**
 * @brief Open a file
 *
 * @param size Size of the file
 * @param filename Name of the file
 * @return int File descriptor
 */
int openFile(int size, char *filename);

/**
 * @brief Read a file
 *
 * @param buffer Buffer to store the file
 * @param size Size of the file
 * @param filename Name of the file
 * @return int Number of bytes read
 */
int readFile(char *buffer, int size, char *filename);

/**
 * @brief Write a file
 *
 * @param buffer Buffer to write to the file
 * @param size Size of the file
 * @param filename Name of the file
 * @return int Number of bytes written
 */
int writeFile(char *buffer, int size, char *filename);

/**
 * @brief Close a file
 *
 * @param filename Name of the file
 * @return int File descriptor
 */
int closeFile(char *filename);

#endif
