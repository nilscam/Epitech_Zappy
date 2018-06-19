/*
** EPITECH PROJECT, 2018
** PSU°zappy_2017
** File description:
** list_utils.c
*/

#include "list.h"

void	list_clear(list_t *self, void (*fct)(void *))
{
	list_node_t	*tmp = self->tail;
	list_node_t	*next;

	while (tmp) {
		next = tmp->next;
		list_node_deinit(tmp, self, fct);
		tmp = next;
	}
	self->tail = NULL;
	self->head = NULL;
	self->size = 0;
}

size_t	list_size(list_t *self)
{
	return self->size;
}
