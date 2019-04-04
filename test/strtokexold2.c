#include <stdio.h>
#include <string.h>

int main ()
{
	char buf[] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/\
bin:/usr/games:/usr/local/games\0";
	int i, j, delim_count = 0;
	const char s[2] = ":";
	char *p = strtok (buf, s);
	char *array[8];

	for (i = 0; buf[i]; i++)
		if (buf[i] == 'u')
			delim_count++;

	printf("count = %i\n", delim_count);

	while (p != NULL)
	{
		array[i++] = p;
		p = strtok (NULL, s);
	}

	for (j = 0; j < 8; ++j)
		printf("%s\n", array[i]);

	return 0;
}
