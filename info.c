#include "shell.h"

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */
void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	/* info->line_count; should not reset */
	info->err_num = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 */
void set_info(info_t *info)
{
	if (info->arg)
		info->argv = strtow(info->arg, " ");
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 */
void free_info(info_t *info)
{
	bfree((void **)&(info->arg));
	ffree(info->argv);
	info->argv = NULL;
	clear_info(info);
}

/**
 * print_info - prints info_t struct
 * @info: struct address
 */
void print_info(info_t *info)
{
	int i = 0;

	printf("info->arg:[%s]\n", info->arg);
	printf("info->argv:%s\n", info->argv ? "" : "[(null)]");
	for (i = 0; info->argv && info->argv[i]; i++)
		printf("\tinfo->argv[%d]:[%s]\n", i, info->argv[i]);

	printf("info->path:[%s]\n", info->path);
	printf("info->line_count:[%d]\n", info->line_count);
	printf("info->err_num:[%d]\n", info->err_num);
	printf("==========================\n");
}
