#include <stdio.h>
#include <stdlib.h>

int input(char *s,int length);

/**
 * main - prompts for text and then prints the input
 * Return: (0) On successful prompt and print
 *        (-1) On failure
 */

int main(void)
{
	char *buffer;
	size_t bufsize = 32;

	buffer = malloc(bufsize * sizeof(char));
	if (!buffer)
		return(1);

	printf("$ ");
	getline(&buffer, &bufsize, stdin);

	printf("%s", buffer);

	return(0);
}
