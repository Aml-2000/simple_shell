#include "shell.h"

void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int free_all);

/**
 * clear_info - initializes info_t struct
 * @info: struct address
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */

void set_info(info_t *info, char **av)
{
	size_t y = 0;

	info->fname = av[0];
	if (info->arg)
	{
		free(info->argv);

	info->argv = strtow(info->arg, " \t");
	if (!info->argv)
	{
		info->argv = malloc(sizeof(char *) * 2);
		if (info->argv)
	{
		info->argv[0] = _strdup(info->arg);
	info->argv[1] = NULL;
	}
	}
	for (y = 0; info->argv && info->argv[y]; y++)
		;
	info->argc = y;

	replace_alias(info);
	replace_vars(info);
	}
}

/**
 * free_info - frees info_t struct fields
 * @info: struct address
 * @free_all: true if freeing all fields
 */
void free_info(info_t *info, int free_all)
{
	if (info->argv)
	{
		size_t i = 0;

		while (i < (size_t)info->argc)
		{
			free(info->argv[i]);
			i++;
		}
		free(info->argv);
		info->argv = NULL;
	}

	info->path = NULL;

	if (free_all)
	{
		free(info->arg);

	if (info->env)
		free_list(&(info->env));

	if (info->history)
		free_list(&(info->history));

	if (info->alias)
		free_list(&(info->alias));

	free(info->environ);
	info->environ = NULL;

	if (info->readfd > 2)
		close(info->readfd);

	_putchar(BUF_FLUSH);
	}
}
