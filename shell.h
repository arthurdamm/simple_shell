#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>

#include "liststr.h"


#define BLA "\033[30m"
#define RED "\033[31m"
#define GRE "\033[32m"
#define YEL "\033[33m"
#define BLU "\033[34m"
#define MAG "\033[35m"
#define CYA "\033[36m"
#define RES "\033[37m"

#define _RED "\033[41m"
#define _GRE "\033[42m"
#define _YEL "\033[43m"
#define _BLU "\033[44m"
#define _MAG "\033[45m"
#define _CYA "\033[46m"
#define _RES "\033[40m"


#define READ_BUF_SIZE 1024

/* 1 if using system getline() */
#define USE_GETLINE 0

#define P (print_info(info))


extern char **environ;


/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@fname: the program filename
 *@env: linked list local copy of environ
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	char *fname;
	list_t *env;
} info_t;

#define INFO_INIT {NULL, NULL, NULL, 0, 0, 0, NULL, NULL}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


/* hsh.c */
int hsh(char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

/* string_functions.c */
int _strlen(char *);
int _strcmp(char *, char *);
char *_strstr(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

/* string_functions2.c */
char *_strcpy(char *, char *);
char *str_concat(char *, char *);
char *_strdup(char *);
void _puts(char *);
int _putchar(char);

/* string_functions3.c */
char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);
unsigned int _strspn(char *, char *);
char *_strpbrk(char *, char *);

/* string_functions4.c */
char **strtow(char *, char *);
char **mystrtok(char *, char *);

/* memory_functions */
void *_calloc(unsigned int, unsigned int);
char *_memset(char *, char, unsigned int);
char *_memcpy(char *, char *, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

/* memory_functions2.c */
int bfree(void **);

/* more_functions.c */
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);
int interactive(void);

/* more_functions2.c */
int _erratoi(char *);
void print_error(info_t *);
int print_d(info_t *);

/* builtin_emulators.c */
int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

/* builtin_emulators2.c */
int _myhistory(info_t *);
int _myalias(info_t *);

/* getline.c module */
ssize_t mygetline(char **, size_t *);
int _getline(char **, size_t *);

/* info.c module */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);
void print_info(info_t *);

/* env.c module */
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

#endif
