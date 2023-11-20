#include "main.h"

/**
 * clear_info_r - initializes info_r struct
 * @info: struct address
 */
void clear_info_r(info_r *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path_cmd = NULL;
	info->arg_count = 0;
}

/**
 * set_info_r - initializes info_r struct
 * @info: struct address
 * @av: argument vector
 */
void set_info_r(info_r *info, char **av)
{
	int i = 0;

	info->prog_fileName = av[0];
	if (info->arg)
	{
		info->argv = SplitStrg_in2(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = strgDuplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->arg_count = i;

		aliasReplace(info);
		varReplace(info);
	}
}

/**
 * free_info_r - frees info_r struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_info_r(info_r *info, int all)
{
	ss_free(info->argv);
	info->argv = NULL;
	info->path_cmd = NULL;
	if (all)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias_node)
			free_list(&(info->alias_node));
		ss_free(info->environ);
			info->environ = NULL;
		free_ptr((void **)info->cmd_buffer);
		if (info->readInput_fd > 2)
			close(info->readInput_fd);
		_putchar(BUFFER_FLUSH);
	}
}

