#include "shell.h"


alias_t *add_alias_end(alias_t **ahead, char *aname, char *avalue);
void free_alias_list(alias_t *ahead);
list_t *add_node_end(list_t **ahead, char *dir);
void free_list(list_t *ahead);

/**
 * add_alias_end - Adds a node to the end of a alias_t linked list.
 * @ahead: A pointer to the head of the list_t list.
 * @aname: The name of the new alias to be added.
 * @avalue: The value of the new alias to be added.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
alias_t *add_alias_end(alias_t **ahead, char *aname, char *avalue)
{
	alias_t *new_node = malloc(sizeof(alias_t));
	alias_t *last;

	if (!new_node)
		return (NULL);

	new_node->Anext = NULL;
	new_node->Aname = malloc(sizeof(char) * (_strlen(aname) + 1));
	if (!new_node->Aname)
	{
		free(new_node);
		return (NULL);
	}
	new_node->Avalue = avalue;
	_strcpy(new_node->Aname, aname);

	if (*ahead)
	{
		last = *ahead;
		while (last->Anext != NULL)
			last = last->Anext;
		last->Anext = new_node;
	}
	else
		*ahead = new_node;

	return (new_node);
}

/**
 * add_node_end - Adds a node to the end of a list_t linked list.
 * @ahead: A pointer to the head of the list_t list.
 * @dir: The directory path for the new node to contain.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new node.
 */
list_t *add_node_end(list_t **ahead, char *dir)
{
	list_t *new_node = malloc(sizeof(list_t));
	list_t *last;

	if (!new_node)
		return (NULL);

	new_node->Adir = dir;
	new_node->Anext = NULL;

	if (*ahead)
	{
		last = *ahead;
		while (last->Anext != NULL)
			last = last->Anext;
		last->Anext = new_node;
	}
	else
		*ahead = new_node;

	return (new_node);
}

/**
 * free_alias_list - Frees a alias_t linked list.
 * @ahead: THe head of the alias_t list.
 */
void free_alias_list(alias_t *ahead)
{
	alias_t *anext;

	while (ahead)
	{
		anext = ahead->Anext;
		free(ahead->Aname);
		free(ahead->Avalue);
		free(ahead);
		ahead = anext;
	}
}

/**
 * free_list - Frees a list_t linked list.
 * @ahead: The head of the list_t list.
 */
void free_list(list_t *ahead)
{
	list_t *anext;

	while (ahead)
	{
		anext = ahead->Anext;
		free(ahead->Adir);
		free(ahead);
		ahead = anext;
	}
}
