#ifndef LISTSTR_H
#define LISTSTR_H

/**
 * struct liststr - singly linked list
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	char *str;
	struct liststr *next;
} list_t;


/* liststr.c module */
list_t *add_node(list_t **, const char *);
list_t *add_node_end(list_t **, const char *);
size_t print_list(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

/* liststr2.c module */
size_t list_len(const list_t *);
char **list_to_strings(list_t *);

#endif
