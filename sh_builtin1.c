#include "shell.h"

/**
 * history_ - function to display the history list
 * @inf: Structure containing potential arguments
 * Return: 0
 */
int history_(pinfo_t *inf)
{
	prt_list(inf->history);
	return (0);
}

/**
 * undo_alias - funnction to set alias to string
 * @inf: parameter struct
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int undo_alias(pinfo_t *inf, char *str)
{
	char *q, d;
	int out;

	q = strchr_(str, '=');
	if (!q)
		return (1);
	d = *q;
	*q = 0;
	out = del_nod(&(inf->alias),
		gt_nod_ind(inf->alias, node_stts(inf->alias, str, -1)));
	*q = d;
	return (out);
}

/**
 * do_alias - function to set alias to string
 * @inf: parameter
 * @str: the string alias
 * Return: 0 on success, 1 on error
 */
int do_alias(pinfo_t *inf, char *str)
{
	char *q;

	q = strchr_(str, '=');
	if (!q)
		return (1);
	if (!*++q)
		return (undo_alias(inf, str));

	undo_alias(inf, str);
	return (addnode_(&(inf->alias), str, 0) == NULL);
}

/**
 * prt_alias - function to print an alias string
 * @nod: alias node
 * Return: 0 on success, 1 on error
 */
int prt_alias(slist_t *nod)
{
	char *q = NULL, *b = NULL;

	if (nod)
	{
		q = strchr_(nod->str, '=');
		for (b = nod->str; b <= q; b++)
			_putchar(*b);
		_putchar('\'');
		_putstr(q + 1);
		_putstr("'\n");
		return (0);
	}
	return (1);
}

/**
 * alias_ - function to work as alias builtin
 * @inf: struct containing potential arguments
 *  Return: 0
 */
int alias_(pinfo_t *inf)
{
	int j = 0;
	char *q = NULL;
	slist_t *nod = NULL;

	if (inf->argc == 1)
	{
		nod = inf->alias;
		while (nod)
		{
			prt_alias(nod);
			nod = nod->next;
		}
		return (0);
	}
	for (j = 1; inf->argv[j]; j++)
	{
		q = strchr_(inf->argv[j], '=');
		if (q)
			do_alias(inf, inf->argv[j]);
		else
			prt_alias(node_stts(inf->alias, inf->argv[j], '='));
	}

	return (0);
}
