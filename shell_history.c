#include "main.h"

/**
 * getHistoryFile - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *getHistoryFile(info_r *info)
{
	char *buf, *dir;

	dir = env_getValue(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (strLen(dir) + strLen(HISTORY_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	copyStrings(buf, dir);
	Cat_2Strgs(buf, "/");
	Cat_2Strgs(buf, HISTORY_FILE);
	return (buf);
}

/**
 * appendHistoryFile - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int appendHistoryFile(info_r *info)
{
	ssize_t fd;
	char *filename = getHistoryFile(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->nXtNode)
	{
		printInp_strg(node->strg, fd);
		printChar_fd('\n', fd);
	}
	printChar_fd(BUFFER_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * readHistoryFile - reads history from file
 * @info: the parameter struct
 *
 * Return: count_historyLine on success, 0 otherwise
 */
int readHistoryFile(info_r *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = getHistoryFile(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			addHistoryList(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		addHistoryList(info, buf + last, linecount++);
	free(buf);
	info->count_historyLine = linecount;
	while (info->count_historyLine-- >= HISTORY_MAXX)
		del_IndexNode(&(info->history), 0);
	renumbHistoryList(info);
	return (info->count_historyLine);
}

/**
 * addHistoryList - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, count_historyLine
 *
 * Return: Always 0
 */
int addHistoryList(info_r *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	addEndNode(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumbHistoryList - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new count_historyLine
 */
int renumbHistoryList(info_r *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->numb = i++;
		node = node->nXtNode;
	}
	return (info->count_historyLine = i);
}

