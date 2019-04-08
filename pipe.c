#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(void)
{
	return (isatty(STDIN_FILENO));
}
