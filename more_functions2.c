#include "shell.h"

/**
 *_erratoi - converts a string to an integer
 *@s: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int i;
	unsigned int result = 0;

	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			if (result > MAX_INT / 10)
				return (-1);
			result *= 10;
			result += (s[i] - '0');
		}
		else
			return (-1);
	}
	return (result);
}
