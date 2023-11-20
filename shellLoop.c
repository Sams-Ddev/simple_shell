#include "main.h"

/**
 * h_sh -The primary loop of the shell program.
 * @info:The structure containing information regarding parameters.
 * @av: The array of arguments passed to the `main()` function.
 *
 * Return: A return value of 0 typically indicates success,
 * while 1 typically signifies an error.
 */
int h_sh(info_r *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		clear_info_r(info);
		if (interative_chk(info))
			printsInp_Strg("$ ");
		printChar_stderr(BUFFER_FLUSH);
		r = getLine_nonLine(info);
		if (r != -1)
		{
			set_info_r(info, av);
			builtin_ret = builtin_cmd_find(info);
			if (builtin_ret == -1)
				find_cmd_PATH(info);
		}
		else if (interative_chk(info))
			_putchar('\n');
		free_info_r(info, 0);
	}
	appendHistoryFile(info);
	free_info_r(info, 1);
	if (!interative_chk(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->exit_error == -1)
			exit(info->status);
		exit(info->exit_error);
	}
	return (builtin_ret);
}

/**
 * builtin_cmd_find - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully,
 * 1 if builtin found but not successful,
 * -2 if builtin signals exit()
 */
int builtin_cmd_find(info_r *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", exit_shell},
		{"env", puts_currentenv},
		{"help", myman},
		{"history", _history_list},
		{"setenv", int_envVar},
		{"unsetenv", del_envVar},
		{"cd", _cd},
		{"alias_node", sim_alias},
		{NULL, NULL}};

	for (i = 0; builtintbl[i].flag_type; i++)
		if (lex_StrgCmp(info->argv[0], builtintbl[i].flag_type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * find_cmd_PATH - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void find_cmd_PATH(info_r *info)
{
	char *path_cmd = NULL;
	int i, k;

	info->path_cmd = info->argv[0];
	if (info->lineCount_inp == 1)
	{
		info->line_count++;
		info->lineCount_inp = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!chk_Delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path_cmd = cmd_findIn_PATH(info, env_getValue(info, "PATH="), info->argv[0]);
	if (path_cmd)
	{
		info->path_cmd = path_cmd;
		fork_exec(info);
	}
	else
	{
		if ((interative_chk(info) || env_getValue(info, "PATH=") || info->argv[0][0] == '/') && is_exec_cmd(info, info->argv[0]))
			fork_exec(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			printError_stdout(info, "not found\n");
		}
	}
}

/**
 * fork_exec - Creates a new process using `fork()` and then
 * executes a (`cmd`) in a separate thread using `exec()`.
 * @info: The structure containing info about funct parameters
 * and return values.
 *
 * Return: void
 */

void fork_exec(info_r *info)
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
		if (execve(info->path_cmd, info->argv, env_strgArray(info)) == -1)
		{
			free_info_r(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				printError_stdout(info, "Permission denied\n");
		}
	}
}

