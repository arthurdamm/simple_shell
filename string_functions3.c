#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

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
