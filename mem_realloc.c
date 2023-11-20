#include "main.h"

/**
 **mem_constByte - Populates memory with a consistent byte value.
 *@s: The reference to the memory region.
 *@b: the byte to fill *s with
 *@n: The quantity of bytes to be loaded.
 *Return: (s) A reference to the memory region represented by "s."
 */
char *mem_constByte(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}

/**
 * ss_free - frees a string of strings
 * @pp: string of strings
 */
void ss_free(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * mem_realloc -Resizes a memory block.
 * @ptr: Reference to the previously allocated memory block using malloc.
 * @old_size: The size of the previous block in bytes.
 * @new_size:The size of the new block in bytes.
 *
 * Return:A reference to the old block, colloquially referred to as
 * "da ol' block.".
 */
void *mem_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

