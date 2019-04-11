#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
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
			if (result > INT_MAX / 10)
				return (-1);
			result *= 10;
			result += (s[i] - '0');
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info)
{
	_puts(info->fname);
	_puts(": ");
	print_d(info);
	_puts(": ");
	_puts(info->argv[0]);
	_puts(": ");
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @args: list of arguments
 *
 * Return: number of characters printed
 */
int print_d(info_t *info)
{
	int i, count = 0;
	int input = info->line_count;
	unsigned int abs, current;

	if (input < 0)
	{
		abs = -input;
		_putchar('-');
		count++;
	}
	else
		abs = input;
	current = abs;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs / i)
		{
			_putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	_putchar('0' + current);
	count++;

	return (count);
}
