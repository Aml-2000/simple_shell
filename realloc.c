#include "shell.h"

/**
 * _memset -adds memory with a constant byte
 * @e: the pointer to the memory area
 * @byt: the byte to fill *s with
 * @amt: the amount of bytes to be filled
 * Return: (e) a pointer to the memory area
 */
char *_memset(char *e, char byt, unsigned int amt)
{
	unsigned int m;

	for (m = 0; m < amt; m++)
		e[m] = byt;
	return (e);
}

/**
 * freestr - frees a string of strings
 * @chch: string of strings
 */
void freestr(char **chch)
{
	char **l = chch;

	if (!chch)
		return;
	while (*chch)
		free(*chch++);
	free(l);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to formal  mallocated block
 * @prev_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to old mem block
 */
void *_realloc(void *ptr, unsigned int prev_size, unsigned int new_size)
{
	char *chk;

	if (ptr == 0)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	if (new_size == prev_size)
		return (ptr);

	chk = malloc(new_size);
	if (!chk)
		return (NULL);

	prev_size = prev_size < new_size ? prev_size : new_size;
	while (prev_size--)
		chk[prev_size] = ((char *)ptr)[prev_size];
	free(ptr);
	return (chk);
}
