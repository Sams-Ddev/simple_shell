#include "main.h"

/**
 * _history_list - Displays the history list, presenting each
 * command on a new line with respective line numbers starting from 0.
 * @info: Structure designed to hold potential arguments,
 * enabling the maintenance of a consistent function prototype.
 *
 * Return: Always 0
 */
int _history_list(info_r *info)
{
	printList_t(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @strg: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_r *info, char *strg)
{
	char *p, c;
	int ret;

	p = findChar_inStrg(strg, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = del_IndexNode(&(info->alias_node),
		getNodeIndex(info->alias_node, nodeWith_pfix(info->alias_node, strg, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @strg:The string representing an alias.
 *
 * Return: Always 0 on success, 1 on error
 */
int set_alias(info_r *info, char *strg)
{
	char *p;

	p = findChar_inStrg(strg, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, strg));

	unset_alias(info, strg);
	return (addEndNode(&(info->alias_node), strg, 0) == NULL);
}

/**
 * print_alias - Prints a string that represents an alias.
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = findChar_inStrg(node->strg, '=');
		for (a = node->strg; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		printsInp_Strg(p + 1);
		printsInp_Strg("'\n");
		return (0);
	}
	return (1);
}

/**
 * sim_alias - Simulates the behavior of the alias builtin (see 'man alias').)
 * @info: A structure containing potential arguments,
 * intended for maintaining a consistent function prototype.
 *
 * Return: Always 0
 */
int sim_alias(info_r *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->arg_count == 1)
	{
		node = info->alias_node;
		while (node)
		{
			print_alias(node);
			node = node->nXtNode;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = findChar_inStrg(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
			print_alias(nodeWith_pfix(info->alias_node, info->argv[i], '='));
	}

	return (0);
}

