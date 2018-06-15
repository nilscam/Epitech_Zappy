/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_get.c
*/

#include "list.h"

void	*list_get_front(list_t *self)
{
	if (self->tail) {
		return self->tail->data;
	}
	return NULL;
}

void	*list_get_back(list_t *self)
{
	if (self->head) {
		return self->head->data;
	}
	return NULL;
}
