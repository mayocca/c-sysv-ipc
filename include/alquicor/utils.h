#ifndef __ALQUICOR_UTILS_H
#define __ALQUICOR_UTILS_H

#include <stdio.h>

#define DEFAULT_PROPERTIES_FILE_PATH "/tmp/alquicor-properties.dat"
#define DEFAULT_REQUESTS_FILE_PATH "/tmp/alquicor-requests.dat"
#define SQUARE_METER_PRICE 2000
#define MAX_PROPERTY_NAME_LENGTH 100
#define MAX_BUYER_LAST_NAME_LENGTH 30
#define PROPERTY_COUNT 4

typedef struct
{
    /* Property ID */
    int id;
    /* Name of the property */
    char name[MAX_PROPERTY_NAME_LENGTH];
    /* Whether the property is reserved */
    int reserved;
    /* Number of square meters */
    int square_meters;
} property_t;

typedef struct
{
    /* Property ID */
    int property_id;
    /* Buyer DNI */
    int buyer_dni;
    /* Buyer last name */
    char buyer_last_name[MAX_BUYER_LAST_NAME_LENGTH];
} request_t;

/**
 * @brief Get the price of a property
 *
 * @param property The property to get the price of
 * @return int The price of the property
 */
int property_get_price(property_t *property);

#endif
