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
	int builtin_ret = 0;
	size_t len = 0;
	char *buf = NULL;
	ssize_t r = 0;
	info_t info[] = { {0, 0, 0, 0} };

	while (r != -1 && builtin_ret != -1)
	{
		if (interactive())
			_puts("$ ");
		buf = NULL;
		len = 0;
		r = mygetline(&buf, &len);
		if (r != -1)
		{
			set_info(info, buf);
			builtin_ret = find_builtin(info);
			if (builtin_ret != -1)
				find_cmd(info->argv);
		}
		if (buf)
			buf = (free(buf), NULL);
		if (info->argv)
			info->argv = (ffree(info->argv), NULL);
		if (0)
			write(STDOUT_FILENO, buf, len);
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
	int i, built_in_ret;
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
 * @argv: arg vector
 *
 * Return: void
 */
void find_cmd(char **argv)
{
	struct stat st;
	char path[1024], **paths, **_paths;
	int found = 0;

	_paths = paths = strtow(_getenv("PATH="), ":");
	if (paths)
	{
		if (_getenv("PATH=")[0] == ':' && !stat(argv[0], &st))
		{
			fork_cmd(argv, NULL);
			found++;
		}
		else
			while (*paths)
			{
				path[0] = '\0';
				strcpy(path, *paths);
				strcat(path, "/");
				strcat(path, argv[0]);
				if (!stat(path, &st))
				{
					found++;
					fork_cmd(argv, path);
					break;
				}
				paths++;
			}
		ffree(_paths);
	}
	if (!found && !stat(argv[0], &st))
		fork_cmd(argv, NULL);
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @argv: arg vector
 * @path: the full command path
 *
 * Return: void
 */
void fork_cmd(char **argv, char *path)
{
	pid_t child_pid;
	int status = 0;

	if (!path)
		path = argv[0];

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		execve(path, argv, NULL);
		exit(98);
	}
	else
	{
		wait(&status);
	}
}
