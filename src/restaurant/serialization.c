#include "restaurant/serialization.h"

void serialize_order(order_t *order, void *buffer, size_t size)
{
    sprintf(buffer, "%c %s", order->type, order->wants_dessert ? "with dessert" : "without dessert");
}

void deserialize_order(void *buffer, order_t *order)
{
    sscanf(buffer, "%c %s", &order->type, order->wants_dessert ? "with dessert" : "without dessert");
}
