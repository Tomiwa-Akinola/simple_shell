#include "shell.h"

/**
 * cmd_ - function to determine if a file is an executable command
 * @inf: struct
 * @path: path to file
 * Return: 1 if true, otherwise 0
 */
int cmd_(pinfo_t *inf, char *path)
{
	struct stat st;

	(void)inf;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dupchar_ - function to duplicate character
 * @path_str: PATH string
 * @stt: the starting index
 * @stp: the stopping index
 * Return: a pointer to the new buffer
 */
char *dupchar_(char *path_str, int stt, int stp)
{
	static char buf[1024];
	int j = 0, m = 0;

	for (m = 0, j = stt; j < stp; j++)
		if (path_str[j] != ':')
			buf[m++] = path_str[j];
	buf[m] = 0;
	return (buf);
}

/**
 * fndpath - function to find command in the PATH string
 * @inf: info struct
 * @path_str: the PATH string
 * @cmd: the command to find
 * Return: full path of command or NULL
 */
char *fndpath(pinfo_t *inf, char *path_str, char *cmd)
{
	int i = 0, curr_ = 0;
	char *path;

	if (!path_str)
		return (NULL);
	if ((strlen_(cmd) > 2) && strchk(cmd, "./"))
	{
		if (cmd_(inf, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!path_str[i] || path_str[i] == ':')
		{
			path = dupchar_(path_str, curr_, i);
			if (!*path)
				strcat_(path, cmd);
			else
			{
				strcat_(path, "/");
				strcat_(path, cmd);
			}
			if (cmd_(inf, path))
				return (path);
			if (!path_str[i])
				break;
			curr_ = i;
		}
		i++;
	}
	return (NULL);
}
