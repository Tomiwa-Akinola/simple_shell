#include "shell.h"

/**
 * strncpy_ - function to  copy a string
 * @dest: destination string to be copied to
 * @src: string to be copied
 * @n: bytes of characters to be copied
 * Return: copied string
 */
char *strncpy_(char *dest, char *src, int n)
{
	int k, l;
	char *s = dest;

	k = 0;
	while (src[k] != '\0' && k < n - 1)
	{
		dest[k] = src[k];
		k++;
	}
	if (k < n)
	{
		l = k;
		while (l < n)
		{
			dest[l] = '\0';
			l++;
		}
	}
	return (s);
}

/**
 * strncat_ - function to concatenate two strings
 * @dest: first string
 * @src: second string
 * @n: amount of bytes to be used
 * Return: concatenated string
 */
char *strncat_(char *dest, char *src, int n)
{
	int k, l;
	char *s = dest;

	k = 0;
	l = 0;
	while (dest[k] != '\0')
		k++;
	while (src[l] != '\0' && l < n)
	{
		dest[k] = src[l];
		k++;
		l++;
	}
	if (l < n)
		dest[k] = '\0';
	return (s);
}

/**
 * strchr_ - function to find character in a string
 * @str: string to be parsed
 * @c: the character to look for
 * Return: str
 */
char *strchr_(char *str, char c)
{
	do {
		if (*str == c)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
