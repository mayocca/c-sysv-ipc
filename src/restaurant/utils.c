#include "restaurant/utils.h"

const char m_menu_type_char[MENU_TYPE_COUNT] = {
    'A',
    'B',
    'C'};

const char *m_menu_type_description[MENU_TYPE_COUNT] = {
    "Lomito",
    "Hamburguesa",
    "Ensalada"};

const int m_menu_type_price[MENU_TYPE_COUNT] = {
    1000,
    2000,
    3000};

menu_type_t menu_type_from_char(char c)
{
    return c - m_menu_type_char[0];
}

char menu_type_to_char(menu_type_t type)
{
    return m_menu_type_char[type];
}

const char *menu_type_description(menu_type_t type)
{
    return m_menu_type_description[type];
}

int menu_type_price(menu_type_t type)
{
    return m_menu_type_price[type];
}
