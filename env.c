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

	while (*env)
	{
		if (starts_with(*env, name))
			return (*env + strlen(name));
		env++;
	}
	return (NULL);
}
