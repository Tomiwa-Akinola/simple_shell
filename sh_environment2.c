#include "shell.h"

/**
 * ret_env - function to return environment
 * @inf: struct
 * Return: 0
 */
char **ret_env(pinfo_t *inf)
{
	if (!inf->environ || inf->localenv_changed)
	{
		inf->environ = ls_tostr(inf->localenv);
		inf->localenv_changed = 0;
	}

	return (inf->environ);
}

/**
 * unset_env - function to temove an environment variable
 * @inf: struct
 * Return: 1 on delete, otherwise 0
 * @var: string env var
 */
int unset_env(pinfo_t *inf, char *var)
{
	slist_t *node = inf->localenv;
	size_t j = 0;
	char *q;

	if (!node || !var)
		return (0);

	while (node)
	{
		q = strchk(node->str, var);
		if (q && *q == '=')
		{
			inf->localenv_changed = del_nod(&(inf->localenv), j);
			j = 0;
			node = inf->localenv;
			continue;
		}
		node = node->next;
		j++;
	}
	return (inf->localenv_changed);
}

/**
 * set_env - function to initialize new/existing environment variable
 * @inf: struct
 * @var: string
 * @value: string env var value
 *  Return: Always 0
 */
int set_env(pinfo_t *inf, char *var, char *value)
{
	char *buf = NULL;
	slist_t *node;
	char *q;

	if (!var || !value)
		return (0);

	buf = malloc(strlen_(var) + strlen_(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	strcat_(buf, "=");
	strcat_(buf, value);
	node = inf->localenv;
	while (node)
	{
		q = strchk(node->str, var);
		if (q && *q == '=')
		{
			free(node->str);
			node->str = buf;
			inf->localenv_changed = 1;
			return (0);
		}
		node = node->next;
	}
	node_end(&(inf->localenv), buf, 0);
	free(buf);
	inf->localenv_changed = 1;
	return (0);
}
