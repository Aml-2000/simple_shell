#include "shell.h"

/**
 * **strtow - splits a string into words
 * @str: the input string
 * @de: the delimeter string
 * Return: a pointer to an array of strings,  NULL on failure
 */

char **strtow(char *str, char *de)
{
	int e, m, i, l, wordnum = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!de)
		de = " ";
	for (e = 0; str[e] != '\0'; e++)
		if (!is_delim(str[e], de) && (is_delim(str[e + 1], de) || !str[e + 1]))
			wordnum++;

	if (wordnum == 0)
		return (NULL);
	a = malloc((1 + wordnum) * sizeof(char *));
	if (!a)
		return (NULL);
	for (e = 0, m = 0; m < wordnum; m++)
	{
		while (is_delim(str[e], de))
			e++;
		i = 0;
		while (!is_delim(str[e + i], de) && str[e + i])
			i++;
		a[m] = malloc((i + 1) * sizeof(char));
		if (!a[m])
		{
			for (i = 0; i < m; i++)
				free(a[i]);
			free(a);
			return (NULL);
		}
		for (l = 0; l < i; l++)
			a[m][l] = str[e++];
		a[m][l] = 0;
	}
	a[m] = NULL;
	return (a);
}

/**
 * **strtow2 - splits a string into words
 * @str: the input string
 * @de: the delimeter
 * Return:  the pointer to an array of strings,  NULL on failure
 */
char **strtow2(char *str, char de)
{
	int e, m, i, l, wordnum = 0;
	char **a;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (e = 0; str[e] != '\0'; e++)
		if ((str[e] != de && str[e + 1] == de) ||
				    (str[e] != de && !str[e + 1]) || str[e + 1] == de)
			wordnum++;
	if (wordnum == 0)
		return (NULL);
	a = malloc((1 + wordnum) * sizeof(char *));
	if (!a)
		return (NULL);
	for (e = 0, m = 0; m < wordnum; m++)
	{
		while (str[e] == de && str[e] != de)
			e++;
		i = 0;
		while (str[e + i] != de && str[e + i] && str[e + i] != de)
			i++;
		a[m] = malloc((i + 1) * sizeof(char));
		if (!a[m])
		{
			for (i = 0; i < m; i++)
				free(a[i]);
			free(a);
			return (NULL);
		}
		for (l = 0; l < i; l++)
			a[m][l] = str[e++];
		a[m][l] = 0;
	}
	a[m] = NULL;
	return (a);
}
