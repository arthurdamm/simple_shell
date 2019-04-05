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
		buf = NULL;
		len = 0;
		r = mygetline(&buf, &len);
		if (starts_with(buf, "exit"))
			break;
		printf("BUF:[%s]\n", buf);
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
	char path[256], **paths, *str;

	_memset(path, '\0', 256);
	if (!stat(argv[0], &st))
		fork_cmd(argv, NULL);
	else
	{
		str = _strdup(_getenv("PATH="));
		printf(">>%s<<\n", str);
		if (!str)
			return;
		paths = mystrtok(str, ":");
		while (*paths)
		{
			//printf("?");
			_memset(path, '\0', 256);
			strcpy(path, *paths);
			strcat(path, "/");
			strcat(path, argv[0]);
			
			//printf("!\n");
			
			if (!stat(path, &st))
			{
				
				printf("PATH:[%s] [%d] \n", path, _strlen(path));
				//puts("IF TRUE!");
				fork_cmd(argv, path);
				break;
			}
			//printf("IF FALSE!");
			
			paths++;

			//printf("#");

		}
		puts("DONE1");
		free(str);
		//puts("DONE2");
	}

}

/**
 * fork_cmd - forks a an exec thread to run cmd
 * @argv: arg vector
 *
 * Return: void
 */
void fork_cmd(char **argv, char *path)
{
	pid_t child_pid;
	int status = 0;

	if (!path)
		path = argv[0];
	while (argv[status])
		printf("FORK: %d [%s]\n", status, argv[status]), status++;
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
