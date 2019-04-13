#include "shell.h"

/**
 * mygetline - gets a line minus the newline
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t mygetline(char **buf_p, size_t *len_p)
{
	static char *buf;
	static size_t i, len;
	ssize_t r = 0;

	_putchar(BUF_FLUSH);
	
	if (!len)
	{
		free(buf);
		buf = NULL;
#if USE_GETLINE
		r = getline(&buf, len_p, stdin);
#else
		r = _getline(&buf, len_p);
#endif

		if (r > 1 && buf[r - 1] == '\n')
		{
			buf[r - 1] = '\0'; /* remove trailing newline */
			r--;
		}
	}
	if (r == -1)
		return (-1);
	/*printf("buf:[%s] [%d]\n", buf, r);*/
	if (_strchr(buf, ';'))
		len = r;

	if (len)
	{
		/* init new iterator to current position */
		size_t j = i;
		char *p = buf + i;

		/* iterate to semicolon or end */
		while (j < len)
		{
			if(buf[j] == ';')
			{
				buf[j] = 0; /* replace semicolon with null */
				break;
			}
			j++;
		}
		i = j + 1;
		if (i >= len)
			i = len = 0;
		*buf_p = p;
		/* printf("p:[%s] _l:[%d] i:[%d] len:[%d]\n", p, _strlen(p), i, len); */
		return (_strlen(p));
	}
	*buf_p = buf;
	return (r);
}

/**
 * read_buf - reads a buffer
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
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

/**
 * _getline - gets the next line of input from STDIN
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
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
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = read_buf(buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len - 1;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);
	if (s)
		_strncat(new_p, buf + i, k - i );
	else
		_strncpy(new_p, buf + i, k - i + 1);
	s += k - i;
	i = k;
	p = new_p;
	if (length)
		*length = s;
	*ptr = p;
	return (s);
}
