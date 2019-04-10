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
	info->argc = 0;
	/* info->line_count; should not reset */
	info->err_num = 0;
	/* info->fname; should not reset */
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 */
void set_info(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " ");
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;
	}
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
	printf("info->argc:[%d]\n", info->argc);
	printf("info->line_count:[%d]\n", info->line_count);
	printf("info->err_num:[%d]\n", info->err_num);
	printf("info->fname:[%s]\n", info->fname);
	printf("info->env:[%s]\n", info->env);
	printf("==========================\n");
}
