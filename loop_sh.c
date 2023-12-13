#include "shell.h"

/**
 * mainsh - the main shell loop
 * @inf: parameter
 * @av: argument vector
 * Return: 0 on success, or 1 on error, or error code
 */
int mainsh(pinfo_t *inf, char **av)
{
	ssize_t b = 0;
	int bn_ret = 0;

	while (b != -1 && bn_ret != -2)
	{
		clr_inf(inf);
		if (interactive(inf))
			_putstr("$ ");
		eputchar_(BUF_FLUSH);
		b = get_dinput(inf);
		if (b != -1)
		{
			set_inf(inf, av);
			bn_ret = fnd_builtin(inf);
			if (bn_ret == -1)
				fnd_cmd(inf);
		}
		else if (interactive(inf))
			_putchar('\n');
		free_inf(inf, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int find_builtin(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_strcmp(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * fnd_cmd - function to find a command in PATH
 * @inf: parameter
 */
void fnd_cmd(pinfo_t *inf)
{
	char *path = NULL;
	int i, k;

	inf->path = inf->argv[0];
	if (inf->lncount_flag == 1)
	{
		inf->ln_count++;
		inf->lncount_flag = 0;
	}
	for (i = 0, k = 0; inf->arg[i]; i++)
		if (!isdelim_(inf->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(inf, _getenv(inf, "PATH="), inf->argv[0]);
	if (path)
	{
		inf->path = path;
		frk_cmd(inf);
	}
	else
	{
		if ((interactive(inf) || _getenv(inf, "PATH=")
			|| inf->argv[0][0] == '/') && is_cmd(inf, inf->argv[0]))
			frk_cmd(inf);
		else if (*(inf->arg) != '\n')
		{
			inf->status = 127;
			print_error(inf, "not found\n");
		}
	}
}

/**
 * frk_cmd - function to fork an exec thread to run command
 * @inf: the parameter
 */
void frk_cmd(pinfo_t *inf)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(inf->path, inf->argv, get_environ(inf)) == -1)
		{
			free_inf(inf, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(inf->status));
		if (WIFEXITED(inf->status))
		{
			inf->status = WEXITSTATUS(inf->status);
			if (inf->status == 126)
				print_error(inf, "Permission not granted\n");
		}
	}
}
