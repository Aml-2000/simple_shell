#include "shell.h"

/**
 * freemem - frees a pointer and voids the address
 * @ptr: address of the pointer to free
 *
 * Return: 1 when free, else 0.
 */
int freemem(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
