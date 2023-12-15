#include "shell.h"

/**
 * env_ - function to print the current environment
 * @inf: struct
 * Return: 0
 */
int env_(pinfo_t *inf)
{
	prt_liststr(inf->localenv);
	return (0);
}

/**
 * get_env - function to get the value of an environment variable
 * @inf: Struct
 * @c: variable
 * Return: null
 */
char *get_env(pinfo_t *inf, const char *c)
{
	slist_t *node = inf->localenv;
	char *q;

	while (node)
	{
		q = strchk(node->str, c);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * setenv_ - function to initialize a new environment variable
 * @inf: struct
 * Return: 0
 */
int setenv_(pinfo_t *inf)
{
	if (inf->argc != 3)
	{
		eputstr("wrong number of arguements\n");
		return (1);
	}
	if (set_env(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * unsetenv_ - function to unset an environment variable
 * @inf: struct
 *  Return: 0
 */
int unsetenv_(pinfo_t *inf)
{
	int j;

	if (inf->argc == 1)
	{
		eputstr("not enough arguements.\n");
		return (1);
	}
	for (j = 1; j <= inf->argc; j++)
		unset_env(inf, inf->argv[j]);

	return (0);
}

/**
 * penv_list - function to populate env linked list
 * @inf: struct
 * Return: 0
 */
int penv_list(pinfo_t *inf)
{
	slist_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		node_end(&node, environ[j], 0);
	inf->localenv = node;
	return (0);
}
