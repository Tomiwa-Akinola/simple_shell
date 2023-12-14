#include "shell.h"

/**
 * strtok_ - function to split a string into words
 * @str: d input string
 * @dstr: the delimeter string
 * Return: ptr to an array of strings, or NULL
 */

char **strtok_(char *str, char *dstr)
{
	int a, b, c, d, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dstr)
		dstr = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!isdelim_(str[a], dstr) && (isdelim_(str[a + 1], dstr) || !str[a + 1]))
			words++;

	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < words; b++)
	{
		while (isdelim_(str[a], dstr))
			a++;
		c = 0;
		while (!isdelim_(str[a + c], dstr) && str[a + c])
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}

/**
 * str_tok - function to split string into words
 * @str: d input string
 * @dstr: delimeter
 * Return: ptr to an array of strings, or NULL
 */
char **str_tok(char *str, char dstr)
{
	int a, b, c, d, words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != dstr && str[a + 1] == dstr) ||
		    (str[a] != dstr && !str[a + 1]) || str[a + 1] == dstr)
			words++;
	if (words == 0)
		return (NULL);
	s = malloc((1 + words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (a = 0, b = 0; b < words; b++)
	{
		while (str[a] == dstr && str[a] != dstr)
			a++;
		c = 0;
		while (str[a + c] != dstr && str[a + c] && str[a + c] != dstr)
			c++;
		s[b] = malloc((c + 1) * sizeof(char));
		if (!s[b])
		{
			for (c = 0; c < b; c++)
				free(s[c]);
			free(s);
			return (NULL);
		}
		for (d = 0; d < c; d++)
			s[b][d] = str[a++];
		s[b][d] = 0;
	}
	s[b] = NULL;
	return (s);
}
