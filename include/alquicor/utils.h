#ifndef __ALQUICOR_UTILS_H
#define __ALQUICOR_UTILS_H

#include <stdio.h>

#define DEFAULT_PROPERTIES_FILE_PATH "/tmp/alquicor-properties.dat"
#define DEFAULT_REQUESTS_FILE_PATH "/tmp/alquicor-requests.dat"
#define SQUARE_METER_PRICE 2000
#define MAX_PROPERTY_NAME_LENGTH 100
#define MAX_BUYER_LAST_NAME_LENGTH 30

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
    /* Buyer ID */
    int buyer_id;
    /* Buyer last name */
    char buyer_last_name[MAX_BUYER_LAST_NAME_LENGTH];
} request_t;

#endif
