#include "shell.h"

/**
 * eputstr - it prints an input string
 * @str: string to be printed
 */
void eputstr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eputchar_(str[i]);
		i++;
	}
}

/**
 * eputchar_ - writes character to standard error
 * @c: character to print
 * Return: On success 1.
 * On error, return -1, and errno is set appropriately.
 */
int eputchar_(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * putfdes - writes character c to a given file descriptor
 * @c: character to print
 * @fdes: filedescriptor to write to
 * Return: On success 1.
 * On error, return -1, and errno is set appropriately.
 */
int putfdes(char c, int fdes)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fdes, buf, i);
		i = 0;
	}
	return (1);
}

/**
 * putsfdes - prints an input string
 * @str: string to be printed
 * @fdes: file descriptor to write to
 * Return: number of characters put
 */
int putsfdes(char *str, int fdes)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += putfdes(*str++, fdes);
	}
	return (i);
}
