#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
	char *argv[] = {"acav", "Test", "Hello World",
			    "This string ends in a newline\n",
			    "I dream to own a tortilla factory",
			    "MORE STRINGS", NULL};

	printf("Before execve\n");
	if (execve(argv[0], argv, NULL) == -1)
	{
		perror("Error:");
	}

	printf("After execve, but you will never see this\n");


	return (0);
}
