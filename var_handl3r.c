#include "main.h"

/**
 * chk_chainDelim - Checks whether current char in the buff is a chain delim.
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of current position in buf
 *
 * Return: 1 if the current char is a chain delimiter, and 0 if it's not.
 */
int chk_chainDelim(info_r *info, char *buf, size_t *p)
{
	size_t j = *p;

	if (buf[j] == '|' && buf[j + 1] == '|')
	{
		buf[j] = 0;
		j++;
		info->cmd_type_buffer = CMD_OR;
	}
	else if (buf[j] == '&' && buf[j + 1] == '&')
	{
		buf[j] = 0;
		j++;
		info->cmd_type_buffer = CMD_AND;
	}
	else if (buf[j] == ';') /* found end of this command */
	{
		buf[j] = 0; /* replace semicolon with null */
		info->cmd_type_buffer = CMD_CHAIN;
	}
	else
		return (0);
	*p = j;
	return (1);
}

/**
 * chk_chainstats - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: The address or reference to the current position in the buffer (buf).
 * @i: The initial or starting position in the buffer (buf).
 * @len: The size or length of the buffer (buf).
 *
 * Return: Void
 */
void chk_chainstats(info_r *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t j = *p;

	if (info->cmd_type_buffer == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}
	if (info->cmd_type_buffer == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*p = j;
}

/**
 * aliasReplace - Substitutes aliases within the tokenized string.
 * @info:The structure containing the parameters used for alias replacement.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int aliasReplace(info_r *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = nodeWith_pfix(info->alias_node, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = findChar_inStrg(node->strg, '=');
		if (!p)
			return (0);
		p = strgDuplicate(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * varReplace - Substitutes variables within the tokenized string.
 * @info: The struct containing the parameters used for vars replacement.
 *
 * Return: 1 if replaced, 0 otherwise
 */
int varReplace(info_r *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!lex_StrgCmp(info->argv[i], "$?"))
		{
			strgReplace(&(info->argv[i]),
				strgDuplicate(similar_itoa(info->status, 10, 0)));
			continue;
		}
		if (!lex_StrgCmp(info->argv[i], "$$"))
		{
			strgReplace(&(info->argv[i]),
				strgDuplicate(similar_itoa(getpid(), 10, 0)));
			continue;
		}
		node = nodeWith_pfix(info->env, &info->argv[i][1], '=');
		if (node)
		{
			strgReplace(&(info->argv[i]),
				strgDuplicate(findChar_inStrg(node->strg, '=') + 1));
			continue;
		}
		strgReplace(&info->argv[i], strgDuplicate(""));

	}
	return (0);
}

/**
 * strgReplace - Substitutes the content of a buffer string.
 * @old: The location or reference to the old string that is being replaced.
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int strgReplace(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

