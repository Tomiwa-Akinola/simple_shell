#include "shell.h"

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	pinfo_t inf[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				eputstr(av[0]);
				eputstr(": 0: Can't open ");
				eputstr(av[1]);
				eputchar_('\n');
				eputchar_(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		inf->readfdes = fd;
	}
	penv_list(inf);
	rd_hist(inf);
	mainsh(inf, av);
	return (EXIT_SUCCESS);
}
