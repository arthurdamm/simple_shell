#include "shell.h"

/**
 * **strtow - splits a string into words
 * @str: the input string
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str)
{
	int i, j, k, numwords = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
	{
		if ((str[i] != ' ') && (str[i + 1] == ' '))
			numwords++;
		if ((str[i] != ' ') && (str[i + 1] == '\0'))
			numwords++;
	}
	if (numwords == 0)
		return (NULL);
	s = malloc((1 + numwords) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < numwords; j++)
	{
		while (str[i] == ' ')
			i++;
		k = 0;
		while (str[i + k] != ' ' && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (k = 0; str[i] && str[i] != ' '; k++)
			s[j][k] = str[i++];
		s[j][k] = 0;
	}
	s[j] = 0;
	return (s);
}
