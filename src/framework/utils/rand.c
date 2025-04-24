#include "framework/utils/rand.h"

#include <stdlib.h>
#include <time.h>

void rand_init(void)
{
    srand((unsigned int)time(NULL));
}

int rand_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}
