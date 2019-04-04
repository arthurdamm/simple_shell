#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * mystrtok - convert a string into an array by iteratively using strtok
 * Return: The generated array
 *         (NULL) On Failure
 */

char **mystrtok(char *str)
{
	int i = 0, j, len;
	const char s[2] = ":";
	char *token;
	char **retarray;

	token = strtok(str, s);

	while (token != NULL)
	{
		len = strlen(token);
		printf("len = %i\n", len);
//		retarray[i] = malloc(sizeof(char) * len);
//		if (retarray[i] == NULL)
//			return(NULL);
//		for (j = 0; token[j]; j++)
//			retarray[i][j] = token[j];
		printf("%s\n", token);
		token = strtok(NULL, s);
		i++;
	}
	return(retarray);
}

/**
 * main - print a mystrtok array
 * Return: (0) Always
 */

int main(void)
{
	char str[200] = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games";
	char **tokarray;
	int i = 0;

	tokarray = mystrtok(str);
	printf("DEBUG 1\n");
//	printf("%s\n", tokarray[i]);
	return(0);
}
