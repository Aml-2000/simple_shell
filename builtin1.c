#include "shell.h"

/**
 * set_alias - sets an alias in the list
 * @info: parameter struct
 * @str: the string alias
 * Return: 1 if it's right, -1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *a;

	a = _strchr(str, '=');
	if (!a)
		return (-1);
	if (!*(a + 1)) /* Check if alias string after '=' is empty */
		return (-1);
	set_alias(info, str);
	if (add_node_end(&(info->alias), str, 0) == NULL)
		return (-1);
	return (1);
}

/**
 * print_alias - prints an alias string
 * @node: the alias node
 * Return: 0 if successful, 1 if there's an error
 */

int print_alias(list_t *node)
{
	char *i = NULL, *q = NULL;

	if (node)
	{
		i = _strchr(node->str, '=');
		for (q = node->str; q <= i; q++)
			_putchar(*q);
		_putchar('\'');
		_puts(i + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
/**
 * _myhistory - displays the history list, one command line, preceded
 *              with line numbers, starting at 0
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myhistory(info_t *info)/*myhistory function , return 0*/
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *e, m;
	int ret;

	e = _strchr(str, '=');
	if (!e)
		return (1);
	m = *e;
	*e = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_indx(info->alias, node_begins_with(info->alias, str, -1)));
	*e = m;
	return (ret);
}


/**
 * _myalias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */

int _myalias(info_t *info)
{
	int a = 0;
	char *w = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (a = 1; info->argv[a]; a++)
	{
		w = _strchr(info->argv[a], '=');
		if (w)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_begins_with(info->alias, info->argv[a], '='));
	}

	return (0);
}

