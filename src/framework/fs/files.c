#include "framework/fs/files.h"

FILE *file_open(const char *path, const char *mode)
{
  FILE *file = fopen(path, mode);

  if (file == NULL)
  {
    perror("Failed to open file");
    return NULL;
  }

  return file;
}

size_t file_read(FILE *file, void *buffer, size_t size, size_t items)
{
  size_t bytes_read = fread(buffer, size, items, file);

  if (bytes_read != items)
  {
    perror("Failed to read file");
    return 0;
  }

  return bytes_read;
}

size_t file_write(FILE *file, const void *buffer, size_t size, size_t items)
{
  size_t bytes_written = fwrite(buffer, size, items, file);

  if (bytes_written != items)
  {
    perror("Failed to write file");
    return 0;
  }

  return bytes_written;
}

int file_close(FILE *file)
{
  int status = fclose(file);

  if (status == EOF)
  {
    perror("Failed to close file");
    return -1;
  }

  return 0;
}
