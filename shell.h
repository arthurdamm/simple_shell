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

/* shell.c module */
void find_cmd(char **argv);
void fork_cmd(char **argv);
ssize_t mygetline(char **buf, size_t *len);

/* strtok.c module */
char **mystrtok(char *str, char *delim);

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

/* env.c module */
char *_getenv(const char *name);

#endif
