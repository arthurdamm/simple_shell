#ifndef SHELL_H
#define SHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>


extern char **environ;


/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
                    allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
} info_t;

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t);
} builtin_table;


/* hsh.c */
int find_builtin(char *arg);
void find_cmd(char **argv);
void fork_cmd(char **argv, char *path);
ssize_t mygetline(char **buf, size_t *len);

/* string_functions.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strstr(char *haystack, char *needle);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* string_functions2.c */
char *_strcpy(char *dest, char *src);
char *str_concat(char *s1, char *s2);
char *_strdup(char *str);
void _puts(char *str);
int _putchar(char c);

/* string_functions3.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);
unsigned int _strspn(char *s, char *accept);
char *_strpbrk(char *s, char *accept);

/* string_functions4.c */
char **strtow(char *str, char *d);
char **mystrtok(char *str, char *delim);

/* memory_functions */
void *_calloc(unsigned int nmemb, unsigned int size);
char *_memset(char *s, char b, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/* more_functions.c */
int is_delim(char c, char *delim);
int _isalpha(int c);
int _atoi(char *s);
char *_getenv(const char *name);
int interactive(void);

/* builtin_emulators.c */
int _myenv(info_t);
int _myexit(info_t);
int _mycd(info_t);
int _myhelp(info_t);

/* builtin_emulators2.c */
int _myhistory(info_t);
int _mysetenv(info_t);
int _myunsetenv(info_t);
int _myalias(info_t);


#endif
