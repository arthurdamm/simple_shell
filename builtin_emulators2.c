#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t info)
{
	char **arg_array;

	arg_array = strtow(info.arg, " ");
	_puts("history call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);
	return(0);
}


/**
 * _mysetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t info)
{
	char **arg_array;

	arg_array = strtow(info.arg, " ");
	_puts("setenv call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);
	return(0);
}


/**
 * _myunsetenv - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t info)
{
	char **arg_array;

	arg_array = strtow(info.arg, " ");
	_puts("unsetenv call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);
	return(0);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t info)
{
	char **arg_array;

	arg_array = strtow(info.arg, " ");
	_puts("alias call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);
	return(0);
}
