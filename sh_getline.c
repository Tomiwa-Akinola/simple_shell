#include "shell.h"

/**
 * input_mybuf - buffers chained commands
 * @inf: parameter
 * @buf: the address of buffer
 * @len: the address of len var
 *
 * Return: bytes read
 */
ssize_t input_mybuf(pinfo_t *inf, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t len_q = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_q, stdin);
#else
		r = _getline(inf, buf, &len_q);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0';
				b--;
			}
			inf->lncount_flag = 1;
			remove_comments(*buf);
			build_history_list(inf, *buf, inf->historycount++);
			{
				*len = b;
				inf->cmd_buf = buf;
			}
		}
	}
	return (b);
}

/**
 * get_dinput - gets a line without the newline
 * @inf: parameter
 * Return: the bytes read
 */
ssize_t get_dinput(pinfo_t *inf)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t b = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_mybuf(inf, &buf, &len);
	if (b == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(inf, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(inf, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			inf->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (b);
}

/**
 * reads_buf - function to read a buffer
 * @inf: parameter
 * @buf: buffer
 * @j: size
 * Return: b
 */
ssize_t reads_buf(pinfo_t *inf, char *buf, size_t *j)
{
	ssize_t b = 0;

	if (*j)
		return (0);
	b = read(inf->readfdes, buf, READ_BUF_SIZE);
	if (b >= 0)
		*j = b;
	return (b);
}

/**
 * _getline - gets next line of input from standard input
 * @inf: parameter
 * @ptr: the address of pointer to buffer
 * @len: size of preallocated ptr buffer if its not NULL
 *
 * Return: s
 */
int _getline(pinfo_t *inf, char **ptr, size_t *len)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, l;
	size_t k;
	ssize_t b = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && len)
		s = *len;
	if (i == l)
		i = l = 0;

	b = reads_buf(inf, buf, &l);
	if (b == -1 || (b == 0 && l == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : l;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (len)
		*len = s;
	*ptr = p;
	return (s);
}

/**
 * sig_inthandler - function to block ctrl-C
 * @sig_num: signal number
 */
void sig_inthandler(__attribute__((unused))int sig_num)
{
	_putstr("\n");
	_putstr("$ ");
	_putchar(BUF_FLUSH);
}
