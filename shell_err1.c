#include "shell.h"

/**
 * err_atoi - function to convert a string to an integer
 * @s: string to be converted
 * Return: 0 if no numbers in string, converted number,
 * or -1 on error
 */
int err_atoi(char *s)
{
	int i = 0;
	unsigned long int res = 0;

	if (*s == '+')
		s++;
	for (i = 0;  s[i] != '\0'; i++)
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			res *= 10;
			res += (s[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_err - function to print an error message
 * @inf: parameter
 * @estr: the string containing specified error type
 * Return: 0 if no numbers in string, converted number, or
 *        -1 on error
 */
void print_err(pinfo_t *inf, char *estr)
{
	eputstr(inf->filename);
	eputstr(": ");
	print_dec(inf->ln_count, STDERR_FILENO);
	eputstr(": ");
	eputstr(inf->argv[0]);
	eputstr(": ");
	eputstr(estr);
}

/**
 * print_dec - prints a decimal
 * @input: input
 * @fdes: filedescriptor to write to
 * Return: number of chars printed
 */
int print_dec(int input, int fdes)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int abs_, current;

	if (fdes == STDERR_FILENO)
		__putchar = eputchar_;
	if (input < 0)
	{
		abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		abs_ = input;
	current = abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * conv_num - function to convert i to a
 * @num: the number
 * @base: the base
 * @flags: argument flags
 * Return: string
 */
char *conv_num(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long d = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		d = -num;
		sign = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = arr[d % base];
		d /= base;
	} while (d != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * rem_com - function to replace first instance of '#' with '\0'
 * @buf: address of string to modify
 * Return: 0;
 */
void rem_com(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
