#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: destination string to be copied
 *@srce: source string
 *@amt: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *srce, int amt)
{
	int i, j;
	char *d = dest;

	i = 0;
	while (srce[i] != '\0' && i < amt - 1)
	{
		dest[i] = srce[i];
		i++;
	}
	if (i < amt)
	{
		j = i;
		while (j < amt)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (d);
}

/**
 **_strncat - concatenates two strings
 *@dest: first string
 *@srce: second string
 *@amt: the amount of bytes to be used
 *Return: the concatenated string
 */

char *_strncat(char *dest, char *srce,  int amt)
{
	int i, j;
	char *d = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (srce[j] != '\0' && j < amt)
	{
		dest[i] = srce[j];
		i++;
		j++;
	}
	if (j < amt)
		dest[i] = '\0';
	return (d);
}

/**
 **_strchr - locates a character in a string
 *@str: the string to be parsed
 *@e: the character to look for
 *Return: (e) a pointer to the memory area
 */
char *_strchr(char *str, char e)
{
	do {
		if (*str == e)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

