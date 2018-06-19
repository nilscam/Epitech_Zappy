/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator_erase.c
*/

#include "list_iterator.h"

void	list_it_erase(list_iterator_t *self, list_fct_t fct)
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
	list_node_deinit(self->node, self->list, fct);
	--self->list->size;
	self->node = next;
}

bool	list_erase_at(list_t *self, list_fct_t fct, int idx)
{
	list_iterator_t	it;
	int		current_idx = 0;

	if (idx < 0 || !INIT(LIST_IT, it, self))
		return false;
	while (list_it_can_iterate(&it)) {
		if (current_idx >= idx) {
			list_it_erase(&it, fct);
			break;
		}
		list_it_iterate(&it);
		++current_idx;
	}
	DEINIT(it);
	return current_idx == idx;
}
