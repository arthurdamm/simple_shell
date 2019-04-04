#include "shell.h"

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
