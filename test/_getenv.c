#include "../shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	int i = 0;

	if (ac == 2)
	{
		printf("[%s]\n", _getenv(av[1]));
		return (0);
	}

	while (environ[i])
	{
		printf("%d] %s\n", i, environ[i]);
		i++;
	}
	return (0);
}

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

/**
 * starts_with - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: 1 if true, 0 if false
 */
int starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (0);
	return (1);
}
