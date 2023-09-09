#include "shell.h"

/**
 * node_begins_with - brings back string that starts with prefix
 * @node: list head pointer
 * @prefix: matching string
 * @emi: the next char to match after prefix
 *
 * Return: match node or null
 */
list_t *node_begins_with(list_t *node, char *prefix, char emi)
{
	char *l = NULL;
		while (node)
	{
		l = begins_with(node->str, prefix);
		if (l && ((emi == -1) || (*l == emi)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * list_len - determines length of linked list
 * @e: first node pointer
 *
 * Return: size of list
 */
size_t list_len(const list_t *e)
{
	size_t m = 0;

	while (e)
	{
		e = e->next;
		m++;
	}
	return (m);
}

/**
 * list_to_strs - returns an array of strings of the list
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strs(list_t *head)
{
	list_t *node = head;
	size_t m = list_len(head), i;
	char **strgs;
	char *str;

	if (!head || !m)
		return (NULL);
	strgs = malloc(sizeof(char *) * (m + 1));
	if (!strgs)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
	str = _strdup(node->str);
		if (!str)
	{
		for (i = 0; i < m; i++)
			free(strgs[i]);
		free(strgs);
		return (NULL);
	}
		strgs[m] = str;
	}
	strgs[m] = NULL;
	return (strgs);
}

/**
 * print_list - prints all elements of a list_t linked list
 * @e: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *e)
{
	size_t m = 0;

	while (e)
	{
		_puts(convert_number(e->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(e->str ? e->str : "(nil)");
		_puts("\n");
		e = e->next;
		m++;
	}
	return (m);
}

/**
 * get_node_indx - gets the index of the node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t get_node_indx(list_t *head, list_t *node)
{
	size_t e = 0;

	while (head)
	{
		if (head == node)
			return (e);
		head = head->next;
		e++;
	}
	return (-1);
}
