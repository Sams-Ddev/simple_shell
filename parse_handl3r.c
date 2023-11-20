#include "main.h"

/**
 * is_exec_cmd - Checks if a file serves as an executable command.
 * @info: the info struct data type
 * @path_cmd: path to the command file
 *
 * Return: 1 if true, 0 otherwise
 */

int is_exec_cmd(info_r *info, char *path_cmd)
{
	struct stat st;

	(void)info;
	if (!path_cmd || stat(path_cmd, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * char_dupx - duplicates(simulation func) characters
 * @pathstrg: the PATH string literal
 * @start: starting index point
 * @stop: stopping index point
 *
 * Return: pointer to new buffer
 */
char *char_dupx(char *pathstrg, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstrg[i] != ':')
			buf[k++] = pathstrg[i];
	buf[k] = 0;
	return (buf);
}

/**
 * cmd_findIn_PATH - finds this command in the PATH strings literal
 * @info: the info struct data type
 * @pathstrg: the PATH strings literal
 * @cmd: the command to be found
 *
 * Return: full path of cmd if found or NULL
 */
char *cmd_findIn_PATH(info_r *info, char *pathstrg, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path_cmd;

	if (!pathstrg)
		return (NULL);
	if ((strLen(cmd) > 2) && ChkStart_haystk(cmd, "./"))
	{
		if (is_exec_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstrg[i] || pathstrg[i] == ':')
		{
			path_cmd = char_dupx(pathstrg, curr_pos, i);
			if (!*path_cmd)
				Cat_2Strgs(path_cmd, cmd);
			else
			{
				Cat_2Strgs(path_cmd, "/");
				Cat_2Strgs(path_cmd, cmd);
			}
			if (is_exec_cmd(info, path_cmd))
				return (path_cmd);
			if (!pathstrg[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

