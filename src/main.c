#include "stdio.h"
#include "stdlib.h"
#include "global.h"

typedef enum {
  HELLO,
  GOODBYE
} MessageType;

typedef struct {
  int x;
  int y;
} Point;

int main(int argc, char *argv[]) {
  g_nValue = 10;
  Point p;
  p.x = 1;
  p.y = 2;
  NULL;

  printf("Hola mundo\n");

  printf("Mensaje de tipo HELLO: %d\n", HELLO);

  return EXIT_SUCCESS;
}
