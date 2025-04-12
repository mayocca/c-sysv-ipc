#include "framework/utils/rand.h"

#include <stdlib.h>
#include <time.h>

void rand_init(void)
{
    srand(time(NULL));
}

int rand_int(int min, int max)
{
    return min + rand() % (max - min + 1);
}

bool rand_bool(float probability)
{
    return rand() < probability * RAND_MAX;
}
