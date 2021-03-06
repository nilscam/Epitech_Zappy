/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.c
*/

#include "player.h"
#include "unique_id.h"

static bool	new_player(player_t *self, va_list *args)
{
	self->map = va_arg(*args, map_t *);
	self->pos = va_arg(*args, map_content_t *);
	self->team = va_arg(*args, team_t *);
	self->name = va_arg(*args, char *);
	self->client = va_arg(*args, client_t *);
	self->id = unique_id(SEED_PLAYER);
	init_player_inventory(&self->inventory);
	return true;
}

static void	delete_player(player_t *self)
{
	player_remove_from_map(self);
	SAFE_FREE(self->name);
}

static const player_t	PLAYER_CLASS = {
	{
		sizeof(player_t),
		"Player",
		(object_cst_t) new_player,
		(object_dst_t) delete_player
	},
	NULL,
	NULL,
	{
		{},
		0
	},
	NULL,
	NULL,
	DIR_DOWN,
	1,
	FOOD_TO_TIME_UNITS,
	0,
	NULL,
	NULL,
	NULL,
	0,
	false,
	false
};

const class_t	*PLAYER = (class_t *) &PLAYER_CLASS;
