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
	size_t len = 0;
	char *buf = NULL, **argv;
	ssize_t r = 0;

	(void)ac;
	(void)av;

	printf("PID: %u PPID: %u\n", getpid(), getppid());

	while (r != -1)
	{
		printf("$ ");
		r = getline(&buf, &len, stdin);
		len = _strlen(buf);
		if (len > 1 && buf[len - 1] == '\n')
			buf[--len] = '\0'; /* remove trailing newline */
		if (starts_with(buf, "exit"))
			break;
		argv = mystrtok(buf, " ");
		fork_cmd(argv);
		if (0)
			write(STDOUT_FILENO, buf, len);
	}
	printf("Exiting...\n");
	return (0);
}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @argv: arg vector
 *
 * Return: void
 */
void fork_cmd(char **argv)
{
	pid_t child_pid;
	int status = 0;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		execve(argv[0], argv, NULL);
		printf("Command not found...\n");
		exit(98);
	}
	else
	{
		wait(&status);
	}
}
