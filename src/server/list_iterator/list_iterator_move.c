/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator_move.c
*/

#include "list_iterator.h"

bool	list_it_can_iterate(list_iterator_t *self)
{
	return self->node != NULL;
}

void	list_it_iterate(list_iterator_t *self)
{
	if (self->node)
		self->node = self->node->next;
}
