#include "shell.h"

/**
 * is_chain - checks if current character is a chain delimeter
 * @info: parameter struct
 * @buff:  character buffer
 * @ptr: address of current position in buff
 *
 * Return: 1 if chain delimeter, otherwise 0
 */
int is_chain(info_t *info, char *buff, size_t *ptr)
{
	size_t r = *ptr;

	if (buff[r] == '|' && buff[r + 1] == '|')
	{
		buff[r] = 0;
		r++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buff[r] == '&' && buff[r + 1] == '&')
	{
		buff[r] = 0;
		r++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buff[r] == ';')
	{
		buff[r] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = r;
	return (1);
}

/**
 * check_chain - checks for chain continuation
 * @info:  parameter struct
 * @buff: the char buffer
 * @ptr: address of current position in buf
 * @e: starting position in buffer
 * @len: length of buffer
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buff, size_t *ptr, size_t e, size_t len)
{
	size_t r = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buff[e] = 0;
			r = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[e] = 0;
			r = len;
		}
	}

	*ptr = r;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *ptr;

	for (e = 0; e < 10; e++)
	{
		node = node_begins_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_vars(info_t *info)
{
	int e = 0;
	list_t *node;

	for (e = 0; info->argv[e]; e++)
	{
		if (info->argv[e][0] != '$' || !info->argv[e][1])
			continue;

		if (!_strcmp(info->argv[e], "$?"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[e], "$$"))
		{
			replace_string(&(info->argv[e]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_begins_with(info->env, &info->argv[e][1], '=');
		if (node)
		{
			replace_string(&(info->argv[e]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[e], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
