#include "shell.h"

/**
 * setmem - function to fill memory with a constant byte
 * @mem: pointer to memory area
 * @byt: byte to fill
 * @n: amount of bytes to be filled
 * Return: pointer to the memory area
 */
char *setmem(char *mem, char byt, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		mem[i] = byt;
	return (mem);
}

/**
 * free_str - funtioln to free a string
 * @st: string of strings
 */
void free_str(char **st)
{
	char **a = st;

	if (!st)
		return;
	while (*st)
		free(*st++);
	free(a);
}

/**
 * mem_realloc - function to reallocate block of memory
 * @ptr: pointer to previous allocated block
 * @prev_byt: size of previous block
 * @new_byt: size of new block
 * Return: pointer to previous block
 */
void *mem_realloc(void *ptr, unsigned int prev_byt, unsigned int new_byt)
{
	char *q;

	if (!ptr)
		return (malloc(new_byt));
	if (!new_byt)
		return (free(ptr), NULL);
	if (new_byt == prev_byt)
		return (ptr);

	q = malloc(new_byt);
	if (!q)
		return (NULL);

	prev_byt = prev_byt < new_byt ? prev_byt : new_byt;
	while (prev_byt--)
		q[prev_byt] = ((char *)ptr)[prev_byt];
	free(ptr);
	return (q);
}

/**
 * free_ptr - funtion to free a pointer
 * @ptr: address of the ptr to free
 * Return: 1 on success, otherwise 0.
 */
int free_ptr(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
