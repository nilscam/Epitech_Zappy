/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** list.c
*/

#include "list.h"

static void	delete_list(list_t *self)
{
	list_clear(self, NULL);
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
	0
};

const class_t	*LIST = (class_t *) &LIST_CLASS;
