#include "framework/fs/files.h"

FILE *file_open(const char *path, const char *mode)
{
  FILE *file = fopen(path, mode);

  if (file == NULL)
  {
    return NULL;
  }

  return file;
}

size_t file_read(FILE *file, void *buffer, size_t size, size_t items)
{
  size_t items_read = fread(buffer, size, items, file);

  if (items_read != items)
  {
    return 0;
  }

  return items_read;
}

size_t file_write(FILE *file, const void *buffer, size_t size, size_t items)
{
  size_t items_written = fwrite(buffer, size, items, file);

  if (items_written != items)
  {
    return 0;
  }

  return items_written;
}

int file_close(FILE *file)
{
  int status = fclose(file);

  if (status == EOF)
  {
    return EOF;
  }

  return 0;
}
