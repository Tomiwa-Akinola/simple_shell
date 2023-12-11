#include "shell.h"

/**
 * clr_inf - initializes the pinfo_t struct
 * @inf: struct address
 */
void clr_inf(pinfo_t *inf)
{
	inf->arg = NULL;
	inf->argv = NULL;
	inf->path = NULL;
	inf->argc = 0;
}

/**
 * set_inf - initializes the pinfo_t struct
 * @inf: the struct address
 * @av: argument vector
 */
void set_inf(pinfo_t *inf, char **av)
{
	int a = 0;

	inf->filename = av[0];
	if (inf->arg)
	{
		inf->argv = strtow(inf->arg, " \t");
		if (!inf->argv)
		{

			inf->argv = malloc(sizeof(char *) * 2);
			if (inf->argv)
			{
				inf->argv[0] = _strdup(inf->arg);
				inf->argv[1] = NULL;
			}
		}
		for (a = 0; inf->argv && inf->argv[a]; a++)
			;
		inf->argc = a;

		replace_alias(inf);
		replace_vars(inf);
	}
}

/**
 * free_inf - it frees pinfo_t struct
 * @inf: the struct address
 * @all: true when freeing all the fields
 */
void free_inf(pinfo_t *inf, int all)
{
	ffree(inf->argv);
	inf->argv = NULL;
	inf->path = NULL;
	if (all)
	{
		if (!inf->cmd_buf)
			free(inf->arg);
		if (inf->localenv)
			free_list(&(inf->localenv));
		if (inf->history)
			free_list(&(inf->history));
		if (inf->alias)
			free_list(&(inf->alias));
		ffree(inf->environ);
			inf->environ = NULL;
		bfree((void **)inf->cmd_buf);
		if (inf->readfolder > 2)
			close(inf->readfolder);
		_putchar(BUF_FLUSH);
	}
}
