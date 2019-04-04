#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		printf("1a - Child execution always comes first. 3s delay\n");
		sleep(3);
		printf("3 - The child has been executed\n");
	}
	else
	{
		sleep(1);
		printf("1b - The parent has not yet waited\n");
		wait(&status);
		sleep(1);
		printf("4 - This is after wait\n");
	}
	return (0);
}
