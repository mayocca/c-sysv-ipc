#ifndef __FRAMEWORK_UTILS_RAND_H
#define __FRAMEWORK_UTILS_RAND_H

/**
 * @brief Initialize the random number generator
 *
 * @return void
 */
void rand_init(void);

/**
 * @brief Generate a random integer between min and max
 *
 * @param min Minimum value (inclusive)
 * @param max Maximum value (exclusive)
 *
 * @return int Random integer between min and max
 */
int rand_int(int min, int max);

#endif
