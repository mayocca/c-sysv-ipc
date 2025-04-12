#ifndef __RESTAURANT_H
#define __RESTAURANT_H

#include <stdbool.h>

#define DESSERT_PRICE 200

typedef enum
{
    TYPE_A = 'A',
    TYPE_B = 'B',
    TYPE_C = 'C'
} menu_type_t;

typedef struct
{
    menu_type_t type;
    char *description;
    int price;
} menu_t;

typedef struct
{
    menu_type_t type;
    bool wants_dessert;
} order_t;

#endif
