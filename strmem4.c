#include "shell.h"

/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

/**
 **_strspn - gets the length of a prefix substring
 *@s: the string to check
 *@accept: the characters (bytes) that can be accepted
 *Return: (count) the length of the initial matching set
 */
unsigned int _strspn(char *s, char *accept)
{
	int i, j, gonext;
	unsigned int count = 0;

	for (i = 0; s[i] != '\0'; i++)
	{
		gonext = 0;
		for (j = 0; accept[j] != '\0'; j++)
		{
			if (s[i] == accept[j])
			{
				gonext = 1;
				count++;
			}
		}
		if (gonext == 0)
			return (count);
	}
	return (0);
}

/**
 **_strpbrk - searches a string for any set of bytes
 *@s: the string to be parsed
 *@accept: the characters to look for
 *Return: (s) a pointer to the first matching instance, or 0 if no matches
 */
char *_strpbrk(char *s, char *accept)
{
	int j;

	for (; *s != '\0'; s++)
		for (j = 0; accept[j] != '\0'; j++)
			if (*s == accept[j])
				return (s);
	return (NULL);
}

/**
 * _isalpha - checks if character is a letter
 * @c: the character to test
 *
 * Return: 1 if c is a letter, 0 otherwise
 */
int _isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

/**
 * _calloc - allocates memory for an array, initialized to 0
 * @nmemb: number of elements
 * @size: byte size of each element
 *
 * Return: void pointer to array space
 */
void *_calloc(unsigned int nmemb, unsigned int size)
{
	char *p;

	if (!nmemb || !size)
		return (NULL);
	p = malloc(nmemb * size);
	if (!p)
		return (NULL);
	nmemb *= size;
	while (nmemb--)
		p[nmemb] = 0;
	return (p);
}
