#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(buf, &len_p);
#endif
		if (r > 1 && (*buf)[r - 1] == '\n')
		{
			(*buf)[r - 1] = '\0'; /* remove trailing newline */
			r--;
		}
		printf("History here? buf = [%s]\n", *buf);
		/* Append history linked list here!!!!! */

		if (r > 0 && _strchr(*buf, ';')) /* is this a command chain? */
		{
			*len = r;
			info->cmd_buf = buf;
		}
	}
	return (r);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg);

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		size_t j = i; /* init new iterator to current buf position */
		char *p = buf + i; /* get pointer for return */

		while (j < len) /* iterate to semicolon or end */
		{
			if (buf[j] == ';') /* found end of this command */
			{
				buf[j] = 0; /* replace semicolon with null */
				break;
			}
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
			i = len = 0; /* reset position and length */

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
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
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

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
		_strncat(new_p, buf + i, k - i);
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
