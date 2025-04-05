#include "tokens.h"

key_t create_token(const char *pathname, int proj_id)
{
    key_t key;

    key = ftok(pathname, proj_id);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    return key;
}
