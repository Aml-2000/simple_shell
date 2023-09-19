#include "shell.h"

/**
 * _myenv - prints the current environment
 * @info: info struct
 * Return: 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an env var
 * @info: info struct
 * @name: env var name
 * Return: if true return a, if not return null
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = begins_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}


/**
 * _mysetenv - sets the value of an environment variable
 * @info: info struct
 * Return: if true return 1, if not return 0
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);
	}

	_unsetenv(info, info->argv[1]);
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);

	return (1);
}

/**
 * _myunsetenv - removes an environment variable
 * @info: info struct
 * Return: if true return 1, if error return 0
 **/

int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}

	for (a = 1; a < info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @info: info struct
 * Return: the size_t if it's 0
 */

int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	info->env = node;
	return (0);
}

