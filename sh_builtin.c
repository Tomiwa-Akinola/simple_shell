#include "shell.h"

/**
 * exit_ - function to exit the shell
 * @inf: Struct containing potential arguments
 * Return: exits with a given exit status
 *        0 if info.argv[0] != "exit"
 */
int exit_(pinfo_t *inf)
{
	int exit_chk;

	if (inf->argv[1])
	{
		exit_chk = err_atoi(inf->argv[1]);
		if (exit_chk == -1)
		{
			inf->status = 2;
			print_err(inf, "Incorrect number: ");
			eputstr(inf->argv[1]);
			eputchar_('\n');
			return (1);
		}
		inf->err_cod = err_atoi(inf->argv[1]);
		return (-2);
	}
	inf->err_cod = -1;
	return (-2);
}

/**
 * cd_ - function to change current directory
 * @inf: Struct containing potential arguments
 *  Return: 0
 */
int cd_(pinfo_t *inf)
{
	char *s, *dr, buffer[1024];
	int cd_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_putstr("TODO: >>getcwd failure emsg here<<\n");
	if (!inf->argv[1])
	{
		dr = get_env(inf, "HOME=");
		if (!dr)
			cd_ret = /* TODO: what should this be? */
				chdir((dr = get_env(inf, "PWD=")) ? dr : "/");
		else
			cd_ret = chdir(dr);
	}
	else if (strcmp_(inf->argv[1], "-") == 0)
	{
		if (!get_env(inf, "OLDPWD="))
		{
			_putstr(s);
			_putchar('\n');
			return (1);
		}
		_putstr(get_env(inf, "OLDPWD=")), _putchar('\n');
		cd_ret = /* TODO: what should this be? */
			chdir((dr = get_env(inf, "OLDPWD=")) ? dr : "/");
	}
	else
		cd_ret = chdir(inf->argv[1]);
	if (cd_ret == -1)
	{
		print_err(inf, "cannot cd to ");
		eputstr(inf->argv[1]), eputchar_('\n');
	}
	else
	{
		set_env(inf, "OLDPWD", get_env(inf, "PWD="));
		set_env(inf, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_ - function to change the current directory
 * @inf: Structure containing potential arguments
 * Return: 0
 */
int help_(pinfo_t *inf)
{
	char **arg_arr;

	arg_arr = inf->argv;
	_putstr("This function is not yet implemented \n");
	if (0)
		_putstr(*arg_arr);
	return (0);
}
