#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @name: env var name
 *
 * Return: the value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		else
			node = node->next;
	}
	return (NULL);
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
	add_node_end(&(info->env), buf);
	free(buf);
	info->env_changed = 1;
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
	list_t *node = info->env;
	size_t i = 0;
	char *p;

	if (info->argc != 2)
		return (_puts("Usage: unsetenv VARIABLE\n"), 1);

	if (!node)
		return (1);

	while (node)
	{
		p = starts_with(node->str, info->argv[1]);
		if (p && *p == '=')
		{
			_puts("Unsetting: ");
			_puts(info->argv[1]);
			printf("<%d>\n", delete_node_at_index(&(info->env), i));
			info->env_changed = 1;
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i]);
	info->env = node;
	return (0);
}
