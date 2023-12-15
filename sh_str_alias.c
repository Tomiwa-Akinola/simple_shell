#include "shell.h"

/**
 * chain_ - function to test if current char is a chain delimeter
 * @inf: struct
 * @buf: char buffer
 * @ads: address of current position in buf
 * Return: 1 if true, 0 otherwise
 */
int chain_(pinfo_t *inf, char *buf, size_t *ads)
{
	size_t a = *ads;

	if (buf[a] == '|' && buf[a + 1] == '|')
	{
		buf[a] = 0;
		a++;
		inf->cmd_buf_type = CMD_OR;
	}
	else if (buf[a] == '&' && buf[a + 1] == '&')
	{
		buf[a] = 0;
		a++;
		inf->cmd_buf_type = CMD_AND;
	}
	else if (buf[a] == ';')
	{
		buf[a] = 0; /* replace semicolon with null */
		inf->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ads = a;
	return (1);
}

/**
 * chk_chain - function to check whether to continue chaining
 * @inf: struct
 * @buf: char buffer
 * @ads: address of current position in buf
 * @a: starting position in buf
 * @len: length of buf
 * Return: Void
 */
void chk_chain(pinfo_t *inf, char *buf, size_t *ads, size_t a, size_t len)
{
	size_t j = *ads;

	if (inf->cmd_buf_type == CMD_AND)
	{
		if (inf->status)
		{
			buf[a] = 0;
			j = len;
		}
	}
	if (inf->cmd_buf_type == CMD_OR)
	{
		if (!inf->status)
		{
			buf[a] = 0;
			j = len;
		}
	}

	*ads = j;
}

/**
 * rep_alias - function to replace an alias in d tokenized string
 * @inf: struct
 * Return: 1 if replaced, otherwise 0
 */
int rep_alias(pinfo_t *inf)
{
	int a;
	slist_t *node;
	char *q;

	for (a = 0; a < 10; a++)
	{
		node = node_stts(inf->alias, inf->argv[0], '=');
		if (!node)
			return (0);
		free(inf->argv[0]);
		q = strchr_(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		inf->argv[0] = q;
	}
	return (1);
}

/**
 * rep_var - function to replace var in the tokenized string
 * @inf: struct
 * Return: 1 if replaced, otherwise 0
 */
int rep_var(pinfo_t *inf)
{
	int a = 0;
	slist_t *node;

	for (a = 0; inf->argv[a]; a++)
	{
		if (inf->argv[a][0] != '$' || !inf->argv[a][1])
			continue;

		if (!strcmp_(inf->argv[a], "$?"))
		{
			rep_str(&(inf->argv[a]),
				_strdup(conv_num(inf->status, 10, 0)));
			continue;
		}
		if (!strcmp_(inf->argv[a], "$$"))
		{
			rep_str(&(inf->argv[a]),
				_strdup(conv_num(getpid(), 10, 0)));
			continue;
		}
		node = node_stts(inf->localenv, &inf->argv[a][1], '=');
		if (node)
		{
			rep_str(&(inf->argv[a]),
				_strdup(strchr_(node->str, '=') + 1));
			continue;
		}
		rep_str(&inf->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * rep_str - function to replace string
 * @oldstr: the address of old string
 * @newstr: new string
 * Return: 1 if replaced, otherwise 0
 */
int rep_str(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
