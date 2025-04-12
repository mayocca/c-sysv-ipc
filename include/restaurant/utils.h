#ifndef __RESTAURANT_UTILS_H
#define __RESTAURANT_UTILS_H

#define DESSERT_PRICE 200

typedef enum
{
    MENU_TYPE_A,
    MENU_TYPE_B,
    MENU_TYPE_C,
    /* Menu types count */
    MENU_TYPE_COUNT
} menu_type_t;

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
    /* Menu type */
    menu_type_t type;
    /* Whether the order wants dessert */
    int wants_dessert;
} order_t;

/**
 * @brief Convert a character to a menu type
 *
 * @param c The character to convert
 * @return menu_type_t The menu type
 */
menu_type_t menu_type_from_char(char c);

/**
 * @brief Convert a menu type to a character
 *
 * @param type The menu type
 * @return char The character
 */
char menu_type_to_char(menu_type_t type);

/**
 * @brief Get the description of a menu type
 *
 * @param type The menu type
 * @return char* The description of the menu type
 */
const char *menu_type_description(menu_type_t type);

/**
 * @brief Get the price of a menu type
 *
 * @param type The menu type
 * @return int The price of the menu type
 */
int menu_type_price(menu_type_t type);

#endif
