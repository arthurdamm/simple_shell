#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(__attribute__((unused))int ac, char **av)
{
	return (hsh(av));
}

/**
 * hsh - main shell loop
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(__attribute__((unused))char **av)
{
	ssize_t r = 0;
	size_t len = 0;
	int builtin_ret = 0;
	info_t info[] = { INFO_INIT };

	while (r != -1 && builtin_ret != -1)
	{
		clear_info(info);
		if (interactive())
			_puts("$ ");
		r = mygetline(&(info->arg), &len);
		if (r != -1)
		{
			set_info(info);
			builtin_ret = find_builtin(info);
			if (builtin_ret != -1)
				find_cmd(info);
		}
		free_info(info);
		if (0)
			write(STDOUT_FILENO, info->arg, _strlen(info->arg));
	}
	if (builtin_ret == -1)
		exit(info->err_num);
	if (interactive())
		printf("return value = %i\n", builtin_ret);
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: 1, 0, or -1 on exit
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = 0;
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
			built_in_ret = builtintbl[i].func(info);
			if (built_in_ret == -1)
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
	struct stat st;
	char path[1024], **paths, **_paths;
	int found = 0;

	_paths = paths = strtow(_getenv("PATH="), ":");
	info->path = info->argv[0];
	if (paths)
	{
		if (_getenv("PATH=")[0] == ':' && !stat(info->argv[0], &st))
		{
			fork_cmd(info);
			found++;
		}
		else
			while (*paths)
			{
				path[0] = '\0';
				strcpy(path, *paths);
				strcat(path, "/");
				strcat(path, info->argv[0]);
				if (!stat(path, &st))
				{
					found++;
					info->path = path;
					fork_cmd(info);
					break;
				}
				paths++;
			}
		ffree(_paths);
	}
	if (!found && !stat(info->argv[0], &st))
		fork_cmd(info);
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
		execve(info->path, info->argv, NULL);
		/* TODO: PUT ERROR FUNCTION */
		exit(98);
	}
	else
	{
		wait(&status);
	}
}
