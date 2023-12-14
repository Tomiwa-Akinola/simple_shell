#include "shell.h"

/**
 * addnode_ - function to add a node to d start of d list
 * @head: address of ptr to head node
 * @str: string field of node
 * @num: node index used by history
 * Return: size of the list
 */
slist_t *addnode_(slist_t **head, const char *str, int num)
{
	slist_t *new_hd;

	if (!head)
		return (NULL);
	new_hd = malloc(sizeof(slist_t));
	if (!new_hd)
		return (NULL);
	setmem((void *)new_hd, 0, sizeof(slist_t));
	new_hd->num = num;
	if (str)
	{
		new_hd->str = _strdup(str);
		if (!new_hd->str)
		{
			free(new_hd);
			return (NULL);
		}
	}
	new_hd->next = *head;
	*head = new_hd;
	return (new_hd);
}

/**
 * node_end - function to add node to the end of list
 * @head: address of ptr to head node
 * @str: str field of node
 * @num: node index
 * Return: the size of list
 */
slist_t *node_end(slist_t **head, const char *str, int num)
{
	slist_t *new_nod, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_nod = malloc(sizeof(slist_t));
	if (!new_nod)
		return (NULL);
	setmem((void *)new_nod, 0, sizeof(slist_t));
	new_nod->num = num;
	if (str)
	{
		new_nod->str = _strdup(str);
		if (!new_nod->str)
		{
			free(new_nod);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_nod;
	}
	else
		*head = new_nod;
	return (new_nod);
}

/**
 * prt_liststr - function to print only string of a list
 * @head: ptr to first node
 * Return: the size of list
 */
size_t prt_liststr(const slist_t *head)
{
	size_t j = 0;

	while (head)
	{
		_putstr(head->str ? head->str : "(nil)");
		_putstr("\n");
		head = head->next;
		j++;
	}
	return (j);
}

/**
 * del_nod - function to delete node at given index
 * @head: address of ptr to first node
 * @ind: index of node to delete
 * Return: 1 on success, otherwise 0
 */
int del_nod(slist_t **head, unsigned int ind)
{
	slist_t *node, *pre_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!ind)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == ind)
		{
			pre_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		pre_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * frlist - function to free all nodes of a list
 * @headptr: address of ptr to head node
 */
void frlist(slist_t **headptr)
{
	slist_t *node, *nxt_node, *head;

	if (!headptr || !*headptr)
		return;
	head = *headptr;
	node = head;
	while (node)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*headptr = NULL;
}
