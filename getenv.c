#include "shell.h"

/**
 * update_environ - updates the environ array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: 1 if successful, 0 if memory allocation fails
 */
int update_environ(info_t *info)
{
	char **new_environ = list_to_strs(info->env);

	if (!new_environ)
	{
		return (0);
	}
	if (info->environ)
	{
		size_t i;

	for (i = 0; info->environ[i] != NULL; i++)
	{
		free(info->environ[i]);
	}
	free(info->environ);
	}

	info->environ = new_environ;
	info->env_changed = 0;
	return (1);
}

/**
 * get_environ - returns the environ array
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Pointer to the environ array
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		if (!update_environ(info))
	{
		return (NULL);
	}
	}
	return (info->environ);
}


/**
 * _unsetenv - Remove an environment variable
 * @info: Structure containing potential arguments
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i = 0;
	char *e;

	if (!node || !var)
		return (0);

	while (node)
	{
		e = begins_with(node->str, var);
		if (e && *e == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments
 * @var: the string env var property
 * @val: the string env var value
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *val)
{
	char *buf = NULL;
	list_t *node;
	char *e;

	if (!var || !val)
		return (0);

	buf = malloc(_strlen(var) + _strlen(val) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, val);
	node = info->env;
	while (node)
	{
		e = begins_with(node->str, var);
		if (e && *e == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

