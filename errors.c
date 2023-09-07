#include "shell.h"

/**
 * _eputchar - writes the char c to stderr
 * @c: The character to print
 *
 * Return: On success 1
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
	write(2, buf, a);
	a = 0;
	}
	if (c != BUF_FLUSH)
	buf[a++] = c;
	return (1);
}

/**
 * _eputs - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int e = 0;

	if (str == 0)
		return;
	while (str[e] != '\0')
	{
		_eputchar(str[e]);
		e++;
	}
}


/**
 * _putfd - writes  character m to given fd
 * @m: character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char m, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (m == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (m != BUF_FLUSH)
		buf[i++] = m;
	return (1);
}

/**
 * _putsfd - prints an input string
 * @str: the string to be printed
 * @fd: file descriptor to be written to
 *
 * Return: the number of chars put
 */
int _putsfd(char *str, int fd)
{
	int i = 0;

	if (str == 0)
		return (0);
	while (*str)
	{
		i += _putfd(*str++, fd);
	}
	return (i);
}

