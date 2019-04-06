#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * mystrtok - convert a delimiter separated string into an array by
 *            iteratively using strtok
 * @str: the input delimiter separated string
 * @delim: the delmiter by which to separate
 * Return: The generated array
 *         (NULL) On Failure
 */

char **mystrtok(char *str, char *delim)
{
	int i, j;
	char *token;
	char **retarray;
	int wordcount = 1;

	if (!str)
		return (NULL);
	for (i = 0; str[i]; i++)
		for (j = 0; delim[j]; j++)
			if (str[i] == delim[j])
			{
				wordcount++;
				break;
			}
	retarray = malloc(sizeof(char *) * (wordcount + 1));
	if (!retarray)
		return (NULL);
	token = strtok(str, delim);
 	for (i = 0; token; i++)
	{
		retarray[i] = token;
		token = strtok(NULL, delim);
	}
	return (retarray);
}

/**
 * main - print a delimited string in mystrok generated array format
 * Return: (0) Always
 */

int main(void)
{
	char str[200] = "/usr/local:/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games";
	char **tokarray;
	int i;

	tokarray = mystrtok(str, ":");
	for (i = 0; tokarray[i]; i++)
		printf("Array element %i = %s\n", i, tokarray[i]);
	free(tokarray);
	return (0);
}
