#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list(info->env_node);
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
	char *buf = NULL;
	if (info->argc != 3)
		return (_puts("Usage: setenv VARIABLE VALUE\n"), 1);

	/* TODO: HACK! LOL ;) */
	info->argc = 2;
	_myunsetenv(info);
	info->argc = 3;
	buf = malloc(_strlen(info->argv[1]) + _strlen(info->argv[2]) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, info->argv[1]);
	_strcat(buf, "=");
	_strcat(buf, info->argv[2]);
	add_node_end(&(info->env_node), buf);
	free(buf);
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
	list_t *node = info->env_node;
	size_t i = 0;
	char *p;

	if (info->argc != 2)
		return (_puts("Usage: unsetenv VARIABLE\n"), 1);

	if(!node)
		return (1);

	while (node)
	{
		p = starts_with(node->str, info->argv[1]);
		if (p && *p == '=')
		{
			delete_node_at_index(&(info->env_node), i);
			i = 0;
			node = info->env_node;
			continue;
		}
		node = node->next;
		i++;
	}
	return (0);
}


int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i]);
	info->env_node = node;
	return (1);
}
