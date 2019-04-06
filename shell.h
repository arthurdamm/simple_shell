#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

extern char **environ;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */

typedef struct builtin
{
	char *type;
	int (*func)(void);
} builtin_table;

/* shell.c module */
void find_cmd(char **argv);
void fork_cmd(char **argv, char *path);
ssize_t mygetline(char **buf, size_t *len);

/* strtok.c module */
char **mystrtok(char *str, char *delim);

/* strtow.c module */
char **strtow(char *str, char *d);

/* string.c module */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, char *needle);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* string2.c module */
char *_strcpy(char *dest, char *src);
char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
void _puts(char *str);
int _putchar(char c);

/* strmem3.c module */
char *_strncpy(char *dest, char *src, int n);
int _atoi(char *s);
char *_strncat(char *dest, char *src, int n);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);

/* strmem4.c module */
char *_strchr(char *s, char c);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);
int _isalpha(int c);
void *_calloc(unsigned int nmemb, unsigned int size);

/* strmem5.c module */
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* env.c module */
char *_getenv(const char *name);

/* builtin_emulators.c module */
int notdone(void);
int _printenv(void);
int _myexit(void);

#endif
