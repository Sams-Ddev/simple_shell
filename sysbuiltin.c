#include "main.h"

/**
 * exit_shell - exits the shell
 * @info:A structure that holds possible arguments and is utilized for
 * maintenance purposes. constant function prototype.
 *
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int exit_shell(info_r *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = convStrg_to_int(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printError_stdout(info, "Illegal number: ");
			printStrg_input(info->argv[1]);
			printChar_stderr('\n');
			return (1);
		}
		info->exit_error = convStrg_to_int(info->argv[1]);
		return (-2);
	}
	info->exit_error = -1;
	return (-2);
}

/**
 * _cd - Alters the current directory of the process.
 * @info: A structure holding potential arguments, used for
 * maintenance purpose of constant function prototype.
 *
 * Return: Always 0
 */
int _cd(info_r *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		printsInp_Strg("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = env_getValue(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = env_getValue(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (lex_StrgCmp(info->argv[1], "-") == 0)
	{
		if (!env_getValue(info, "OLDPWD="))
		{
			printsInp_Strg(s);
			_putchar('\n');
			return (1);
		}
		printsInp_Strg(env_getValue(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = env_getValue(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printError_stdout(info, "can't cd to ");
		printStrg_input(info->argv[1]), printChar_stderr('\n');
	}
	else
	{
		init_setenv(info, "OLDPWD", env_getValue(info, "PWD="));
		init_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * myman - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int myman(info_r *info)
{
	char **arg_array;

	arg_array = info->argv;
	printsInp_Strg("help call works. Function not yet implemented \n");
	if (0)
		printsInp_Strg(*arg_array); /* temp att_unused workaround */
	return (0);
}
