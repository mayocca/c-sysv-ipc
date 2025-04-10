#include "fs/files.h"
#include <stdio.h>

FILE *open_file(const char *path, const char *mode)
{
  return fopen(path, mode);
}

size_t read_file(FILE *file, char *buffer, size_t size)
{
  return fread(buffer, 1, size, file);
}

size_t write_file(FILE *file, char *buffer, size_t size)
{
  return fwrite(buffer, 1, size, file);
}

int close_file(FILE *file)
{
  return fclose(file);
}
