#include "shell.h"

/**
 * _erratoi - converts a string to an integer
 * @t: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */

int _erratoi(char *t)
{
	int i;
	unsigned long int result = 0;

	if (*t == '+')
		t++;

	for (i = 0; t[i] != '\0'; i++)
	{
		if (t[i] >= '0' && t[i] <= '9')
		{
			result *= 10;
			result += (t[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}

	return ((int)result);
}

/**
 * print_error - prints an error message
 * @info: the parameter & return info struct
 * @errst: str containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

void print_error(info_t *info, char *errst)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(errst);
}


/**
 * print_d - func prints a decimal number (base 10)
 * @num: the input
 * @d: file descriptor to write into
 *
 * Return: number of characters printed
 */

int print_d(int num, int d)
{
	int (*putchar_func)(char) = (d == STDERR_FILENO) ? _eputchar : _putchar;
	int a, count = 0;
	unsigned int absolute_value, current;

	if (num < 0)
	{
		absolute_value = (unsigned int)(-num);
		putchar_func('-');
		count++;
	}
	else
		absolute_value = (unsigned int)num;

	current = absolute_value;

	for (a = 1000000000; a > 1; a /= 10)
	{
		if (absolute_value / a)
		{
			putchar_func('0' + current / a);
			count++;
		}
		current %= a;
	}

	putchar_func('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function
 * @n: number
 * @b: base
 * @flags: argument flags
 *
 * Return: string
 */

char *convert_number(long int n, int b, int flags)
{
	static char buffer[50];
	char *conversion_array =
		(flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	char sign = 0;
	char *ptr;
	long absolute_value = (long)((flags & CONVERT_UNSIGNED) ? n : labs(n));

	if (!(flags & CONVERT_UNSIGNED) && n < 0)
	{
	absolute_value = -n;
	sign = '-';
	}

	ptr = &buffer[49];
	*ptr = '\0';

	do {
	--ptr;
	*ptr = conversion_array[absolute_value % b];
	absolute_value /= b;
	} while (absolute_value != 0);

	if (sign)
	*--ptr = sign;

	return (ptr);
}

/**
 * remove_comments - func replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}

