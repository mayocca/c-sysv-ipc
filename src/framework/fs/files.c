#include "framework/fs/files.h"
#include "framework/utils/logging.h"

FILE *file_open(const char *path, const char *mode)
{
  FILE *file = fopen(path, mode);

  if (file == NULL)
  {
    log0("Failed to open file");
    return NULL;
  }

  return file;
}

size_t file_read(FILE *file, void *buffer, size_t size, size_t items)
{
  return fread(buffer, size, items, file);
}

size_t file_write(FILE *file, const void *buffer, size_t size, size_t items)
{
  size_t items_written = fwrite(buffer, size, items, file);

  if (items_written != items)
  {
    log0("Failed to write file");
    return 0;
  }

  return items_written;
}

int file_close(FILE *file)
{
  int status = fclose(file);

  if (status == EOF)
  {
    log0("Failed to close file");
    return -1;
  }

  return 0;
}
