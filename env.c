#include "shell.h"

/**
 * _getenv - gets the value of an environ variable
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(const char *name)
{
	char **env = environ;
	char *ret = NULL;

	while (*env)
	{
		ret = starts_with(*env++, name);
		if (ret && *ret)
			return (ret);
	}
	return (NULL);
}
