#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: the destination
 * @src: the source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * str_concat - concatenaste two strings
 * @s1: the first string
 * @s2: the second string
 *
 * Return: pointer to the concatenated string
 */
char *str_concat(char *s1, char *s2)
{
	int length1 = 0, length2 = 0;
	char *ret;

	while (s1 && *s1++)
		length1++;
	while (s2 && *s2++)
		length2++;
	ret = malloc(sizeof(char) * (length1 + length2 + 1));
	if (!ret)
		return (NULL);
	ret += length1 + length2;
	*ret = '\0';
	for (s2--; length2--;)
		*--ret = *--s2;
	for (s1--; length1--;)
		*--ret = *--s1;
	return (ret);
}

/**
 * _strdup - duplicates a string
 * @str: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *_strdup(char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - prints an input string
 *@str: the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
