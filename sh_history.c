#include "shell.h"

/**
 * gt_file_history - function to get history file
 * @inf: parameter
 * Return: string containg history file
 */

char *gt_file_history(pinfo_t *inf)
{
	char *buf, *dir;

	dir = _getenv(inf, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strlen_(dir) + strlen_(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	strcat_(buf, "/");
	strcat_(buf, HIST_FILE);
	return (buf);
}

/**
 * write_hist - function to  create a file or append to an existing file
 * @inf: the parameter
 * Return: 1 on success, otherwise -1
 */
int write_hist(pinfo_t *inf)
{
	ssize_t fdes;
	char *filename = gt_file_history(inf);
	slist_t *node = NULL;

	if (!filename)
		return (-1);

	fdes = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fdes == -1)
		return (-1);
	for (node = inf->history; node; node = node->next)
	{
		putsfdes(node->str, fdes);
		putfdes('\n', fdes);
	}
	putfdes(BUF_FLUSH, fdes);
	close(fdes);
	return (1);
}

/**
 * rd_hist - function to read history from file
 * @inf: the parameter
 * Return: historycount on success, otherwise 0
 */
int rd_hist(pinfo_t *inf)
{
	int i, last = 0, lncount = 0;
	ssize_t fdes, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = gt_file_history(inf);

	if (!filename)
		return (0);

	fdes = open(filename, O_RDONLY);
	free(filename);
	if (fdes == -1)
		return (0);
	if (!fstat(fdes, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fdes, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fdes);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			bd_hist_list(inf, buf + last, lncount++);
			last = i + 1;
		}
	if (last != i)
		bd_hist_list(inf, buf + last, lncount++);
	free(buf);
	inf->historycount = lncount;
	while (inf->historycount-- >= HIST_MAX)
		delete_node_at_index(&(inf->history), 0);
	renum_hist(inf);
	return (inf->historycount);
}

/**
 * bd_hist_list - function to add entry to a history linked list
 * @inf: structure containing potential arguments
 * @buf: buffer
 * @lncount: the history linecount, histcount
 *
 * Return: Always 0
 */
int bd_hist_list(pinfo_t *inf, char *buf, int lncount)
{
	slist_t *node = NULL;

	if (inf->history)
		node = inf->history;
	add_node_end(&node, buf, lncount);

	if (!inf->history)
		inf->history = node;
	return (0);
}

/**
 * renum_hist - function to renumber history linked list after changes
 * @inf: Structure containing potential arguments
 * Return: new historycount
 */
int renum_hist(pinfo_t *inf)
{
	slist_t *node = inf->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (inf->historycount = i);
}
