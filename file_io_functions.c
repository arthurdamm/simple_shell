#include "shell.h"

/**
 * get_history_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *dir;

	dir = _getenv(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * create_file - creates a file, or appends to an existing file
 * @filename: the name of the file to create
 * @text_content: a NULL terminated string to wtire to the file
 * Return: (1) On success, the number of letters that could be read and printed
 *        (-1) On failure (file can not be created, file can not be written,
 *             write “fails”, etc…)
 *        (-1) if filename is NULL
 */

int write_history(info_t *info)
{
	ssize_t fd, wrlen = -1;
	int i = 0, j = 0;
	char *filename = get_history_file(info), buf[WRITE_BUF_SIZE];
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY, 0600);
	free(filename);
	if (fd == -1)
		return (-1);
	buf[0] = 0;
	for (i = 0, node = info->history; node; node = node->next)
	{
		if (i + _strlen(node->str) + 1 > WRITE_BUF_SIZE)
		{
			wrlen = write(fd, buf, i);
			buf[i = 0] = 0;
		}

		for (j = 0; node->str[j]; i++, j++)
			buf[i] = node->str[j];
		buf[i++] = '\n';
	}
	if (i)
		wrlen = write(fd, buf, i);
	close(fd);
	if (wrlen == -1)
		return (-1);

	return (1);
}

/**
 * read_textfile - reads text file and returns the number of lines in the file
 * @filename: the text file to be read
 * Return: On success, the number of letters that could be read and printed
 *         (0) if write fails or does not write the expected amount of bytes
 *         (0) if filename is NULL, or if file can not be opened or read
 */

int read_history(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (linecount-- >= 4096)
		delete_node_at_index(&info->history, 0);
	return (linecount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 *          constant function prototype.
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}
