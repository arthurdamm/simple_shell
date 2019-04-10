#include "shell.h"

/**
 * init_info - initializes info_t struct
 * @info: struct address
 */
void init_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;

	info->err_num = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @arg: line buffer
 */
void set_info(info_t *info, char *arg)
{
	if (arg)
	{
		info->arg = arg;
		info->argv = strtow(arg, " ");
	}
}
