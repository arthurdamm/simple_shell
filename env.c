#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	int i;

	if (!info->env)
		return (0);

	for (i = 0; info->env[i]; i++)
	{
		_puts(info->env[i]);
		_putchar('\n');  /* _puts does not add a newline */
	}
	return (0);
}

/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("setenv call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);  /* temp att_unused workaround */
	return (0);
}

/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	char **arg_array;

	free(environ[0]);
	arg_array = info->argv;
	_puts("unsetenv call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);  /* temp att_unused workaround */
	return (0);
}

/**
 * copy_environ - makes a local copy of environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int copy_environ(info_t *info)
{
	int i = 0;
	char **env = NULL;

	if (!environ)
		return (0);

	for (i = 0; environ[i]; i++)
		;
	env = malloc(sizeof(char *) * (i + 1));
	if (!env)
		return (0);
	for (i = 0; environ[i]; i++)
	{
		env[i] = malloc(_strlen(environ[i]) + 1);
		if (!env[i])
		{
			for (int j = 0; j < i; j++)
				free(env[j]);
			return (0);
		}
		_strcpy(env[i], environ[i]);

	}
	env[i] = NULL;
	info->env = env;
	return (1);
}
