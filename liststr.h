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


list_t *add_node(list_t **, const char *);
list_t *add_node_end(list_t **, const char *);
size_t print_list(const list_t *);
void free_list(list_t **);

#endif
