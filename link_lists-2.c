#include "main.h"

/**
 * List_length - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t List_length(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->nXtNode;
		i++;
	}
	return (i);
}

/**
 * strg_listSTRUCT - returns an array of strings of the list->strg
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **strg_listSTRUCT(list_t *head)
{
	list_t *node = head;
	size_t i = List_length(head), j;
	char **strs;
	char *strg;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->nXtNode, i++)
	{
		strg = malloc(strLen(node->strg) + 1);
		if (!strg)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		strg = copyStrings(strg, node->strg);
		strs[i] = strg;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * printList_t - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t printList_t(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		printsInp_Strg(similar_itoa(h->numb, 10, 0));
		_putchar(':');
		_putchar(' ');
		printsInp_Strg(h->strg ? h->strg : "(nil)");
		printsInp_Strg("\n");
		h = h->nXtNode;
		i++;
	}
	return (i);
}

/**
 * nodeWith_pfix - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *nodeWith_pfix(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = ChkStart_haystk(node->strg, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->nXtNode;
	}
	return (NULL);
}

/**
 * getNodeIndex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t getNodeIndex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->nXtNode;
		i++;
	}
	return (-1);
}

