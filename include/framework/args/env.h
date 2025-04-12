#ifndef __FRAMEWORK_ARGS_ENV_H
#define __FRAMEWORK_ARGS_ENV_H

/**
 * @brief Get the value of an environment variable
 *
 * @param key Environment variable key
 * @param default_value Default value to return if the environment variable is not set
 * @return char* Value of the environment variable, default value if not set
 */
char *env_get(const char *key, char *default_value);

#endif
