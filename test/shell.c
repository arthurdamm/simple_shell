#include "shell.h"

int main(int ac, char **av)
{
	int i = 0;
	size_t len = 0;
	char *buf = NULL;
	ssize_t r = 0;
	char *argv[] = {"/bin/ls", "-l", "/vagrant", NULL};

	(void)ac;
	while(av[i])
		printf("[%s]\n", av[i++]);

	printf("PID: %u PPID: %u\n", getpid(), getppid());


	while (r != -1)
	{
		printf("$ ");
		r = getline(&buf, &len, stdin);
		if (!strncmp(buf, "exit", 4))
			break;
		for (i = 0; i < 5; i++)
			forkme(argv);
		printf("FORK FINISHED %d!\n", getpid());
		if (r > 0)
			write(STDOUT_FILENO, buf, len);
	}
	printf("Exiting...\n");

	printf("Done\n");
	return (0);
}

void forkme(char **argv)
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
	}
	else
	{
		wait(&status);
	}
}