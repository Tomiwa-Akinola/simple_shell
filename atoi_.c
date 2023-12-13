#include "shell.h"

/**
 * interactive - true if shell is interactive mode
 * @inf: the struct address
 * Return: 1 if in interactive mode, 0 if otherwise
 */
int interactive(pinfo_t *inf)
{
	return (isatty(STDIN_FILENO) && inf->readfdes <= 2);
}

/**
 * isdelim_ - checks if the character is a delimeter
 * @c: character to check
 * @delim: delimeter string
 * Return: 1 if true, 0 if false
 */
int isdelim_(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * isalpha_ - checks for alphabet
 * @c: character to input
 * Return: 1 if c is an alphabet, 0 if otherwise
 */

int isalpha_(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * atoi_ - converts string to integer
 * @s: the string to be converted
 * Return: 0 if no number is in the string, otherwise, converted number
 */

int atoi_(char *s)
{
	int i, sign = 1, flag = 0, out;
	unsigned int res = 0;

	for (i = 0;  s[i] != '\0' && flag != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			flag = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		out = -res;
	else
		out = res;

	return (out);
}
