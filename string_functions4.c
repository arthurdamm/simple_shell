#include "shell.h"

/**
 * **strtow - splits a string into words
 * @str: the input string
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *d)
{
	int i, j, k, m, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (is_delim(str[i], d))
			i++;
		k = 0;
		while (!is_delim(str[i + k], d) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}

#if USE_STRTOK
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
#endif
