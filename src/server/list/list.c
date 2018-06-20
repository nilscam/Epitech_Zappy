/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list.c
*/

#include "list.h"

static bool	new_list_alloc(list_t *self, va_list *args)
{
	self->max_buffers = va_arg(*args, size_t);
	self->buffers = malloc(sizeof(list_node_t) * self->max_buffers);
	if (!self->buffers)
		return false;
	for (int i = 0; i < self->max_buffers; ++i) {
		list_node_init(self->buffers + i, NODE_UNUSED, NULL, i);
	}
	return true;
}

static void	delete_list(list_t *self)
{
	list_clear(self, NULL);
	SAFE_FREE(self->buffers);
}

static const list_t	LIST_CLASS = {
	{
		sizeof(list_t),
		"List",
		NULL,
		(object_dst_t) delete_list
	},
	NULL,
	NULL,
	0,
	NULL,
	0,
	0
};

static const list_t	LIST_ALLOC_CLASS = {
	{
		sizeof(list_t),
		"List Alloc",
		(object_cst_t) new_list_alloc,
		(object_dst_t) delete_list
	},
	NULL,
	NULL,
	0,
	NULL,
	0,
	0
};

const class_t	*LIST = (class_t *) &LIST_CLASS;
const class_t	*LIST_ALLOC = (class_t *) &LIST_ALLOC_CLASS;
