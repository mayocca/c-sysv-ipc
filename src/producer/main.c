#include <stdio.h>
#include <stdlib.h>
#include "utils/logging.h"

int main(void) {
  int g_nValue = 0;

  LOG_INFO("Hola mundo\n");

  LOG_INFO("Mensaje de tipo HELLO: %d\n", g_nValue);

  return EXIT_SUCCESS;
}
