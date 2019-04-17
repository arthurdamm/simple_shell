#include "shell.h"

/**
 * hsh - main shell loop
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;
	info_t info[] = { INFO_INIT };

	populate_env_list(info);
	_setenv(info, "OLDPWD", _getenv(info, "HOME="));
	while (r != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive())
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		free_info(info, 0);
		if (0)
			write(STDOUT_FILENO, info->arg, _strlen(info->arg));
	}
	append_history(info);
	free_info(info, 1);
	if (builtin_ret == -2)
		exit(info->err_num);
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *path = NULL;

	info->path = info->argv[0];
	if (info->err_flag == 1)
	{
		info->line_count++;
		info->err_flag = 0;
	}
	path = find_path(_getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if (is_cmd(info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
			print_error(info, "not found\n");
	}
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		execve(info->path, info->argv, get_environ(info));
		/* TODO: PUT ERROR FUNCTION */
		exit(98);
	}
	else
	{
		wait(&status);
	}
}
