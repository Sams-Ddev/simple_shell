#include "main.h"

/**
 * env_strgArray - Returns copy of string-array of our environ.
 * @info: A structure that holds potential arguments,
 * used to maintain a consistent function prototype.
 *
 * Return: Always 0
 */

char **env_strgArray(info_r *info)
{
	while (!info->environ || (info->modified_env != 0))
	{
		info->environ = strg_listSTRUCT(info->env);
		info->modified_env = 0;
	}

	return (info->environ);
}

/**
 * del_setenv - Deletes or removes an environment variable.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int del_setenv(info_r *info, char *var)
{
	list_t *node = info->env;
	char *p;
	size_t i = 0;

	if (node == NULL || var == NULL)
		return (0);

	while (node != NULL)
	{
		p = ChkStart_haystk(node->strg, var);
		
		while (p != NULL && *p == '=')
		{
			info->modified_env = del_IndexNode(&(info->env), i);
			i = 0;
			node = info->env;
		}
		node = node->nXtNode;
		i++;
	}
	return (info->modified_env);
}

/**
 * init_setenv -Initializes new environment var or modifies an existing one.
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *
 * Return: Always 0
 */
int init_setenv(info_r *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (var == NULL || value == NULL)
		return (0);

	buf =(char *) malloc(strLen(var) + strLen(value) + 2);
	if (buf == NULL)
		return (1);
	copyStrings(buf, var);
	Cat_2Strgs(buf, "=");
	Cat_2Strgs(buf, value);
	node = info->env;
	while (node)
	{
		p = ChkStart_haystk(node->strg, var);
		while (p && *p == '=')
		{
			free(node->strg);
			node->strg = buf;
			info->modified_env = 1;
			return (0);
		}
		node = node->nXtNode;
	}
	addEndNode(&(info->env), buf, 0);
	free(buf);
	info->modified_env = 1;
	return (0);
}

