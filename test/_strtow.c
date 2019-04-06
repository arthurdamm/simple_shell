#include "../shell.h"

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char **ret;
	(void)ac;
	
	ret = strtow(av[1], av[2] ? av[2] : " ");
	if (!ret)
		return (printf("Return NULL!\n"), 0);
	while (*ret)
		printf("[%s] ", *ret++);
	printf("\n");
	return (0);
}
