#include "shell.h"

/**
 * is_cmd - checks if a file is an executable command
 * @path: file path
 * @info: info struct
 *
 * Return: 1 if right, otherwise 0
 */
int is_cmd(info_t *info, char *path)
{
	struct stat emi;

	(void)info;
	if (!path || stat(path, &emi))
		return (0);

	if (emi.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @begin: starting index
 * @end: stopping index
 *
 * Return: new buffer pointer
 */
char *dup_chars(char *pathstr, int begin, int end)
{
	static char buffer[1024];
	int e = 0, m = 0;

	for (m = 0, e = begin; e < end; e++)
		if (pathstr[e] != ':')
			buffer[m++] = pathstr[e];
	buffer[m] = 0;
	return (buffer);
}

/**
 * find_path - finds command in the PATH string
 * @info: the info struct
 * @pathstr: the PATH string
 * @comd: the command to find
 *
 * Return: full commad path  if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *comd)
{
	int e = 0, stat_pnt = 0;
	char *emil;

	if (pathstr == 0)
		return (NULL);
	if ((_strlen(comd) > 2) && begins_with(comd, "./"))
	{
		if (is_cmd(info, comd))
			return (comd);
	}
	while (1)
	{
		if (!pathstr[e] || pathstr[e] == ':')
		{
			emil = dup_chars(pathstr, stat_pnt, e);
			if (!*emil)

				_strcat(emil, comd);
			else
			{
				_strcat(emil, "/");
				_strcat(emil, comd);
			}
			if (is_cmd(info, emil))
				return (emil);
			if (!pathstr[e])
				break;
			stat_pnt = e;
		}
		e++;
	}
	return (NULL);
}
