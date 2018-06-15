/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.c
*/

#include "map.h"

static bool	new_map(map_t *self, va_list *args)
{
	int	x = va_arg(*args, int);
	int	y = va_arg(*args, int);

	self->size.x = x;
	self->size.y = y;
	self->cases_buff = malloc(sizeof(map_content_t) * (x * y));
	self->cases = malloc(sizeof(map_content_t *) * (y + 1));
	self->players = NEW(LIST);
	if (!self->cases_buff || !self->cases || !self->players)
		return false;
	init_map_contents(self);
	return true;
}

static void	delete_map(map_t *self)
{
	SAFE_FREE(self->cases_buff);
	SAFE_FREE(self->cases);
	list_clear(self->players, delete_class);
	SAFE_DELETE(self->players);
}

static const map_t	MAP_CLASS = {
	{
		sizeof(map_t),
		"Map",
		(object_cst_t) new_map,
		(object_dst_t) delete_map
	},
	{
		0,
		0
	},
	NULL,
	NULL,
	NULL
};

const class_t	*MAP = (class_t *) &MAP_CLASS;
