/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator_ops.c
*/

#include "list_iterator.h"

void	list_it_erase(list_iterator_t *self, void (*fct)(void *))
{
	list_node_t	*next;

	if (!self->node)
		return;
	next = self->node->next;
	if (self->node->prev)
		self->node->prev->next = self->node->next;
	else
		self->list->tail = self->node->next;
	if (self->node->next)
		self->node->next->prev = self->node->prev;
	else
		self->list->head = self->node->prev;
	if (fct)
		fct(self->node->data);
	free(self->node);
	--self->list->size;
	self->node = next;
}

void	*list_it_get(list_iterator_t *self)
{
	return (self->node ? self->node->data : NULL);
}

void	list_it_set(list_iterator_t *self, void *data)
{
	if (self->node)
		self->node->data = data;
}
