#include "../shell.h"


int _getline(char **ptr, size_t *length);
ssize_t read_buf(char *buf, size_t *i);
/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */

		/*
		printf(">>[%d]buf:[%s]\n", r, buf);
		printf("buf==[%d]", buf[r-1]=='\n');

		puts("pre realloc");
		printf("s:%d r:%d\n", s, r);
		*/


int main(int ac, char **av)
{
	char *buf = NULL;
	size_t len = 0;
	int r = 0, i = 0;
	(void)ac;
	(void)av;
	while (i < 25)
	{
		r = _getline(&buf, &len);
		printf("len: [" GRE "%d" RES "]\n", len);
		printf("strlen: [" BLU "%d" RES "]\n", _strlen(buf));
		printf("buf: [" RED "%s" RES "]\n", buf);
		printf("getline1(): <" CYA "%d" RES ">\n", r);

		free(buf);
		buf = NULL;
		i++;
		if (r == -1)
			break;
	}
	return (0);
}

/**
 * _getline - gets the next line of input from STDIN
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @len: size of preallocated ptr buffer if not NULL
 *
 * Return:
 */
int _getline(char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	char *p = NULL, *new_p = NULL;
	ssize_t r = 0, s = 0;
	char *c;

	p = *ptr;
	if (p)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned)(c - buf): len - 1;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i);
	s += k - i;
	i = k;
	/* cat in a newline here */
	/* new_p = _strcat(new_p, "\n"); */
	/* end cat */
	p = new_p;
	*length = s;
	*ptr = p;
	return (s);
}

ssize_t read_buf(char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(STDIN_FILENO, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}
