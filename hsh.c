#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	int builtin_ret = 0;
	size_t len = 0;
	char *buf = NULL, **argv;
	ssize_t r = 0;

	(void)ac;
	(void)av;

	while (r != -1)
	{
		if (interactive())
			_puts("$ ");
		buf = NULL;
		len = 0;
		r = mygetline(&buf, &len);
		if (r != -1)
		{
			builtin_ret = find_builtin(buf);
			argv = strtow(buf, " ");
			find_cmd(argv);
			ffree(argv);
		}
		free(buf);
		if (0)
			write(STDOUT_FILENO, buf, len);
	}
	if (interactive())
		printf("return value = %i\n", builtin_ret);
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @arg: arg vector
 *
 * Return: 1, 0, or -1 on exit
 */
int find_builtin(char *arg)
{
	char **p;
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
	info_t info[] = {
		{arg, p = strtow(arg, " "), 0, 0}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			built_in_ret = builtintbl[i].func(info);
			if (built_in_ret == -1)
				break;
		}
	ffree(p);
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

/**
 * mygetline - gets a line minus the newline
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t mygetline(char **buf, size_t *len)
{
#if USE_GETLINE
	ssize_t r = getline(buf, len, stdin);
#else
	ssize_t r = _getline(buf, len);
#endif
	if (r > 1 && (*buf)[r - 1] == '\n')
	{
		(*buf)[r - 1] = '\0'; /* remove trailing newline */
		r--;
	}
	return (r);
}
