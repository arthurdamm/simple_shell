#include "../shell.h"

extern char **environ;
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	int i = 0;

	(void)ac; (void)av;

	while (environ[i])
	{
		printf("%d] %s\n", i, environ[i]);
		i++;
	}
	return (0);
}