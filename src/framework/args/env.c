#include "framework/args/env.h"

#include <stdlib.h>

char *env_get(const char *key, const char *default_value)
{
    char *value = getenv(key);
    if (value == NULL)
    {
        return default_value;
    }
    return value;
}