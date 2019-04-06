#include "shell.h"

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

/**
 * notdone - placeholder function for unfinished built in emulators
 *
 *  Return: Always 0
 */
int notdone(void)
{
	printf("Not implemented yet.\n");
	return (0);
}
