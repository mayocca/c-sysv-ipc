#include "files.h"
#include "stdio.h"

int openFile(int size, char *filename) {
  FILE *file = fopen(filename, "r");
  // fopen
  // freopen
  // open
  // creat
  return 0;
}

int readFile(char *buffer, int size, char *filename) {
  // fscanf
  // fread
  //
  // fgets
  // fgetc
  return 0;
}

int writeFile(char *buffer, int size, char *filename) {
  // fprintf
  // fwrite
  //
  // fputs
  // fputc
  return 0;
}

int closeFile(char *filename) {
  // fclose
  // close
  return 0;
}
