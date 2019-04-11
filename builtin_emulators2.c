#include "shell.h"

/**
 * _myhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("history call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);  /* temp att_unused workaround */
	return (0);
}

/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("alias call works. Function not yet implemented \n");
	if (0)
		puts(*arg_array);  /* temp att_unused workaround */
	return (0);
}
