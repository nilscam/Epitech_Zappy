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
	int	players_per_team = va_arg(*args, int);
	int	nb_teams = va_arg(*args, int);

	self->size.x = x;
	self->size.y = y;
	self->cases_buff = malloc(sizeof(map_content_t) * (x * y));
	self->cases = malloc(sizeof(map_content_t *) * (y + 1));
	self->players = NEW(LIST_ALLOC, 255);
	self->eggs = NEW(LIST_ALLOC, 255);
	if (!self->cases_buff || !self->cases
		|| !self->players || !self->eggs)
		return false;
	return init_map_contents(self, players_per_team, nb_teams);
}

static void	delete_map(map_t *self)
{
	if (self->cases_buff && self->cases)
		deinit_map_contents(self);
	list_clear(self->eggs, delete_class);
	SAFE_DELETE(self->eggs);
	list_clear(self->players, delete_class);
	SAFE_DELETE(self->players);
	SAFE_FREE(self->cases);
	SAFE_FREE(self->cases_buff);
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
	NULL,
	NULL
};

const class_t	*MAP = (class_t *) &MAP_CLASS;
