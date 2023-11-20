#include "main.h"

/**
 * puts_currentenv -Prints the current environment.
 * @info: A structure that holds possible arguments,
 * aiming to maintain a consistent function prototype.
 * Return: Always 0
 */
int puts_currentenv(info_r *info)
{
	putsStrg_List(info->env);
	return (0);
}
/*######################################################################*/
/**
 * env_getValue - Retrieves the value of an environment variable.
 * @info: A structure holding potential arguments,
 * used for maintaining consistent functionality and structure.
 * @name: Environment variable name.
 *
 * Return: the value
 */

char *env_getValue(info_r *info, const char *name)
{
	char *name_buffer;
	list_t *node;
	char *buffer;
	int bytes_read;
	char *value_ptr;

	/* Check the environment variables*/
	char *env_value = getenv(name);
	if (env_value)
	{
		return env_value;
	}
	/* Create a temporary buffer to store the environment variable name*/
	name_buffer = malloc(strlen(name) + 1);

	if (!name_buffer)
	{
		return (NULL);
	}
	strcpy(name_buffer, name);

	/* Iterate through the linked list of environment variables*/
	node = info->env;

	while (node)
	{
		/* Open the file descriptor for the environment variable node*/
		int fd = open(node->strg, O_RDONLY);
		if (fd < 0)
		{
			continue;
		}
		/* Read the contents of the environment variable file*/
		buffer = malloc(1024);

		if (!buffer)
		{
			close(fd);
			free(name_buffer);
			return (NULL);
		}

		bytes_read = read(fd, buffer, 1024);
		if (bytes_read < 0)
		{
			close(fd);
			free(buffer);
			free(name_buffer);
			return (NULL);
		}

		/* Close the file descriptor*/
		close(fd);

		/* Search for the environment variable name within the buffer*/
		value_ptr = strstr(buffer, name_buffer);

		if (value_ptr)
		{
			/* Extract the environment variable value*/
			char *value = value_ptr + strlen(name_buffer) + 1;

			/* Free the temporary buffers and return the value*/
			free(buffer);
			free(name_buffer);
			return (value);
		}

		/* Free the buffer and continue to the next node*/
		free(buffer);
	}
	/* Free the temporary buffer and return NULL*/
	free(name_buffer);
	return (NULL);
}
/*##################################################################*/

/*-----------------------------------*/
/**
 * int_envVar - Initialize a  verynew working environment variable,
 * or modify an existing one
 * @info:A structure designed to contain possible arguments,
 * with the purpose of maintaining a consistent function prototype.
 * Return: Always 0
 */
int int_envVar(info_r *info)
{
	if (info->arg_count != 3)
	{
		printStrg_input("Incorrect number of arguements\n");
		return (1);
	}
	if (init_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}
/*#################################################################*/
/**
 * del_envVar - Delete an environment variable.
 * @info: A data structure designed to hold potential arguments,
 * ensuring a consistent function prototype.
 * Return: Always 0
 */
int del_envVar(info_r *info)
{
	int i;

	if (info->arg_count == 1)
	{
		printStrg_input("Too few arguements.\n");
		return (1);
	}

	for (i = 1; i <= info->arg_count; i++)
	{
		 del_setenv(info, info->argv[i]);
	}

	return (0);
}
/*################################################################*/

/**
 * populate_envList - populates env linked list
 * @info: A data structure designed to hold potential
 * arguments, ensuring a consistent function prototype.
 * Return: Always 0
 */
int populate_envList(info_r *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addEndNode(&node, environ[i], 0);
	info->env = node;
	return (0);
}
/*####################################################################*/
