/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator_ops.c
*/

#include "list_iterator.h"

void	*list_it_get(list_iterator_t *self)
{
	return (self->node ? self->node->data : NULL);
}

void	list_it_set(list_iterator_t *self, void *data)
{
	if (self->node)
		self->node->data = data;
}
