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
	int i, built_in_ret;
	size_t len = 0;
	char *buf = NULL, **argv;
	ssize_t r = 0;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _printenv},
		{"help", notdone},
		{"history", notdone},
		{"setenv", notdone},
		{"cd", notdone},
		{"alias", notdone},
		{NULL, NULL}
	};
	(void)ac;
	(void)av;

	printf("PID: %u PPID: %u\n", getpid(), getppid());

	while (r != -1)
	{
		_puts("$ ");
		buf = NULL;
		len = 0;
		r = mygetline(&buf, &len);
		if (r == -1)
			break;
		for (i = 0; builtintbl[i].type; i++)
			if (starts_with(buf, builtintbl[i].type))
			{
				built_in_ret = builtintbl[i].func();
				if (built_in_ret == -1)
					return(0);
			}
		argv = strtow(_strdup(buf), " ");
		find_cmd(argv);
		if (0)
			write(STDOUT_FILENO, buf, len);
	}
	return (0);
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
	char path[1024], **paths, *str;

	if (!stat(argv[0], &st))
		fork_cmd(argv, NULL);
	else
	{
		str = _strdup(_getenv("PATH="));
		if (!str)
			return;
		paths = strtow(str, ":");
		while (*paths)
		{
			path[0] = '\0';
			strcpy(path, *paths);
			strcat(path, "/");
			strcat(path, argv[0]);
			if (!stat(path, &st))
			{
				fork_cmd(argv, path);
				break;
			}
			paths++;
		}
		free(str);
	}

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
	ssize_t r = getline(buf, len, stdin);

	if (r > 1 && (*buf)[r - 1] == '\n')
	{
		(*buf)[r - 1] = '\0'; /* remove trailing newline */
		r--;
	}
	return (r);
}
