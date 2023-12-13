#include "shell.h"

/**
 * strlen_ - function to return length of string
 * @s: the string with the length to check
 * Return: length of string
 */
int strlen_(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * strcmp_ - compares two strings.
 * @s1: first string
 * @s2: second string
 * Return: negative if s1 < s2, positive if s1 > s2, 0 if s1 = s2
 */
int strcmp_(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * strchk - checks if string starts with c
 * @string: string to search
 * @c: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *strchk(const char *string, const char *c)
{
	while (*c)
		if (*c++ != *string++)
			return (NULL);
	return ((char *)string);
}

/**
 * strcat_ - function to concatenate two strings
 * @dest: destination buffer
 * @src: source buffer
 * Return: a pointer to destination buffer
 */
char *strcat_(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
