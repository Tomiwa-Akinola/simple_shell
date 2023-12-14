#include "shell.h"

/**
 * lslen_ - function to  determine the length of a linked list
 * @f: pointer to first node
 * Return: size of list
 */
size_t lslen_(const slist_t *f)
{
	size_t j = 0;

	while (f)
	{
		f = f->next;
		j++;
	}
	return (j);
}

/**
 * ls_tostr - function to return array of string
 * @f: pointer to first node
 * Return: arr of string
 */
char **ls_tostr(slist_t *f)
{
	slist_t *node = f;
	size_t i = lslen_(f), j;
	char **strs;
	char *str;

	if (!f || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(strlen_(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * prt_list - function to print all elements linked list
 * @f: pointer to first node
 * Return: d size of list
 */
size_t prt_list(const slist_t *f)
{
	size_t j = 0;

	while (f)
	{
		_putstr(conv_num(f->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_putstr(f->str ? f->str : "(nil)");
		_putstr("\n");
		f = f->next;
		j++;
	}
	return (j);
}

/**
 * node_stts - function to return node
 * @nod: pointer to the ls head
 * @match: string to match
 * @c: the next character after prefix to match
 * Return: matched node or null
 */
slist_t *node_stts(slist_t *nod, char *match, char c)
{
	char *q = NULL;

	while (nod)
	{
		q = strchk(nod->str, match);
		if (q && ((c == -1) || (*q == c)))
			return (nod);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * gt_nod_ind - function to get d index of a node
 * @hd: ptr to head
 * @nd: ptr to node
 * Return: index of node, or -1
 */
ssize_t gt_nod_ind(slist_t *hd, slist_t *nd)
{
	size_t j = 0;

	while (hd)
	{
		if (hd == nd)
			return (j);
		hd = hd->next;
		j++;
	}
	return (-1);
}
