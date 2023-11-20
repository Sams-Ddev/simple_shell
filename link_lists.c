#include "main.h"

/**
 * addStartNode - adds a node to the start of the list
 * @head: address of pointer to head node
 * @strg: string field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *addStartNode(list_t **head, const char *strg, int numb)
{
	list_t *new_head;

	if (!head)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	mem_constByte((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (strg)
	{
		new_head->strg = strgDuplicate(strg);
		if (!new_head->strg)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->nXtNode = *head;
	*head = new_head;
	return (new_head);
}

/**
 * addEndNode - adds a node to the end of the list
 * @head: address of pointer to head node
 * @strg: string field of node
 * @numb: node index used by history
 *
 * Return: size of list
 */
list_t *addEndNode(list_t **head, const char *strg, int numb)
{
	list_t *new_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	mem_constByte((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (strg)
	{
		new_node->strg = strgDuplicate(strg);
		if (!new_node->strg)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->nXtNode)
			node = node->nXtNode;
		node->nXtNode = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * putsStrg_List - prints only the strings element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t putsStrg_List(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		printsInp_Strg(h->strg ? h->strg : "(nil)");
		printsInp_Strg("\n");
		h = h->nXtNode;
		i++;
	}
	return (i);
}

/**
 * del_IndexNode - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int del_IndexNode(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->nXtNode;
		free(node->strg);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prev_node->nXtNode = node->nXtNode;
			free(node->strg);
			free(node);
			return (1);
		}
		i++;
		prev_node = node;
		node = node->nXtNode;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->nXtNode;
		free(node->strg);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}

