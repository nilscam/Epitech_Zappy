/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list_iterator.c
*/

#include "list_iterator.h"

static bool	new_list_iterator(list_iterator_t *self, va_list *args)
{
	self->list = va_arg(*args, list_t *);
	self->node = self->list->tail;
	return true;
}

static const list_iterator_t	LIST_IT_CLASS = {
	{
		sizeof(list_iterator_t),
		"List Iterator",
		(object_cst_t) new_list_iterator,
		NULL
	},
	NULL,
	NULL
};

const class_t	*LIST_IT = (class_t *) &LIST_IT_CLASS;
