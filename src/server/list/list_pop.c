/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_pop.c
*/

#include "list.h"

void	*list_pop_front(list_t *self)
{
	list_node_t	*tail = self->tail;
	void		*data = NULL;

	if (tail) {
		self->tail = self->tail->next;
		data = tail->data;
		free(tail);
		if (self->tail)
			self->tail->prev = NULL;
	}
	return data;
}

void	*list_pop_back(list_t *self)
{
	list_node_t	*head = self->head;
	void		*data = NULL;

	if (head) {
		self->head = self->head->prev;
		data = head->data;
		free(head);
		if (self->head)
			self->head->next = NULL;
	}
	return data;
}
