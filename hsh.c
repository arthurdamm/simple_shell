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
	int i;
	size_t len = 0;
	char *buf = NULL, **argv;
	ssize_t r = 0;
	builtin_table builtintbl[] = {
		{"env"},
		{"help"},
		{"history"},
		{"setenv"},
		{"cd"},
		{"alias"},
		{NULL}
	};
	(void)ac;
	(void)av;

	printf("PID: %u PPID: %u\n", getpid(), getppid());

	while (r != -1)
	{
		printf("$ ");
		buf = NULL;
		len = 0;
		r = mygetline(&buf, &len);
		if (starts_with(buf, "exit"))
			break;
		for (i = 0; builtintbl[i].type; i++)
			if (starts_with(buf, builtintbl[i].type))
			    printf("match!\n");
		argv = mystrtok(_strdup(buf), " ");
		find_cmd(argv);
		if (0)
			write(STDOUT_FILENO, buf, len);
	}
	printf("Exiting...\n");
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
		paths = mystrtok(str, ":");
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
		printf("Command not found...\n");
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

/**
 * _printenv - prints the current environment
 *
 *  Return: Always 0
 */
int _printenv(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
	return (0);
}
