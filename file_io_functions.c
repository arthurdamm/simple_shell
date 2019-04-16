#include "shell.h"

/**
 * append_history - adds getline input to a history file
 * @info: info
 *Return: nothin
 */

void append_history(__attribute__((unused))info_t *info)
{
	char buffer[1024];

	/* TODO	dir = _getenv(info, "HOME="); */
	_strcpy(buffer, "/home/vagrant/");
	_strcat(buffer, ".simple_shell_history");
	create_file(buffer, "Test history\n");
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

int create_file(const char *filename, char *text_content)
{
	ssize_t fd, wrlen;
	int i = 0;

	if (filename == NULL)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0600);
	if (fd == -1)
		return (-1);

	if (text_content)
	{
		while (text_content[i])
			i++;
		wrlen = write(fd, text_content, i);
	}
	close(fd);
	if (wrlen == -1)
		return (-1);

	return (1);
}
