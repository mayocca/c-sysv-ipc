#ifndef __RESTAURANT_H
#define __RESTAURANT_H

#include <stdbool.h>

#define DESSERT_PRICE 200

typedef enum
{
    MENU_TYPE_A,
    MENU_TYPE_B,
    MENU_TYPE_C,
    /* Menu types count */
    MENU_TYPE_COUNT
} menu_type_t;

const char menu_type_char[MENU_TYPE_COUNT] = {
    'A',
    'B',
    'C'};

const int menu_type_price[MENU_TYPE_COUNT] = {
    1000,
    2000,
    3000};

typedef struct
{
    /* Menu type */
    menu_type_t type;
    /* Menu description */
    char *description;
    /* Menu price */
    int price;
} menu_t;

typedef struct
{
    /* Whether the order has been processed */
    bool processed;
    /* Menu type */
    menu_type_t type;
    /* Whether the order wants dessert */
    bool wants_dessert;
} order_t;

#endif
