#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(__attribute__((unused)) info_t *info)
{
	int i;

	for (i = 0; environ[i]; i++)
	{
		_puts(environ[i]);
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

	if (!environ)
	{
		return (info->err_num);
	}
	for (i = 0; environ[i]; i++)
		;
	return (1);
}
