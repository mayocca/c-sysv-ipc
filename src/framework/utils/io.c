#include "framework/utils/io.h"

#include <stdio.h>
#include <string.h>

#define PROMPT "-> "

void io_read_line(char *buffer, int size)
{
    printf(PROMPT);
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
}

int io_read_int(void)
{
    int result;
    printf(PROMPT);
    scanf("%d", &result);
    return result;
}

void io_clear_buffer(void)
{
    while (getchar() != '\n')
        ;
}
