#include "alquicor/utils.h"

int property_get_price(property_t *property)
{
    return property->square_meters * SQUARE_METER_PRICE;
}
