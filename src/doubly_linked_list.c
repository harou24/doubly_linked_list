#include "doubly_linked_list.h"
#include <stdlib.h>

t_list	*list_create()
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->first = NULL;
	list->last = NULL;
	return (list);
}

t_node	*node_create(void *content)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_node	*list_get_last(t_list *list)
{
	return (list->last);
}

void	list_add_front(t_list *list, t_node *to_add)
{
	if (list->first)
		list->first->prev = to_add;
	to_add->next = list->first;
	to_add->prev = NULL;
	list->first = to_add;
}

void	list_add_back(t_list *list, t_node *to_add)
{
	t_node	*last;

	last = list_get_last(list);
	to_add->prev = last;
	last->next = to_add;
	to_add->next = NULL;
}

size_t	list_size(t_list *list)
{
	int			size;
	t_node	*node;

	size = 0;
	node = list->first;
	while (node)
	{
		size++;
		node = node->next;
	}
	return (size);
}

void	list_iter(t_list *list, void (*function)(void*))
{
	t_node	*node;

	node = list->first;
	while (node)
	{
		function(node->content);
		node = node->next;
	}
}

void	list_delete_item(t_list *list, t_node *to_delete, void (*ft_delete)(void*))
{
	if (to_delete->next)
		to_delete->next->prev = to_delete->prev;
	else
		list->last = to_delete->prev;
	if (to_delete->prev)
		to_delete->prev->next = to_delete->next;
	else
		list->first = to_delete->next;
	ft_delete(to_delete->content);
	free(to_delete);
}

void	list_clear(t_list *list, void (*ft_delete)(void*))
{
	t_node	*node;
	t_node	*tmp;

	node = list->first;
	while (node)
	{
		tmp = node;
		node = node->next;
		list_delete_item(list, tmp, ft_delete);
	}
}

void	list_destroy(t_list *list, void (*ft_delete)(void*))
{
	list_clear(list, ft_delete);
	free(list);
}
