#include "shell.h"

/**
 * add_node - adds a node to the beginning of a list
 * @head: A pointer to a pointer to the head of the linked list
 * @num: node index used by history
 * @str: string field of node
 *
 * Return: size of list
 */

list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head;

	if (head == 0)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (new_head == 0)
		return (NULL);
	_memset((void *)new_head, 0, sizeof(list_t));
	new_head->num = num;
	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *head;
	*head = new_head;
	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: size of list
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - prints only the element of the string linked- list
 * @e: first node pointer
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *e)
{
	size_t m = 0;

	while (e)
	{
		_puts(e->str ? e->str : "(nil)");
		_puts("\n");
		e = e->next;
		m++;
	}
	return (m);
}

/**
 * delete_node_at_index - deletes node at the index
 * @head: address of pointer to first node
 * @indx: index of node to delete
 *
 * Return: on success 1, on failure 0
 */
int delete_node_at_index(list_t **head, unsigned int indx)
{
	list_t *node, *former_node;
	unsigned int m = 0;

	if (!head || !*head)
		return (0);

	if (!indx)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (m == indx)
		{
			former_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		m++;
		former_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all lists node
 * @head_pntr: address of pointer to node
 *
 * Return: void
 */
void free_list(list_t **head_pntr)
{
	list_t *node, *next_node, *head;

	if (!head_pntr || !*head_pntr)
		return;
	head = *head_pntr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_pntr = NULL;
}
