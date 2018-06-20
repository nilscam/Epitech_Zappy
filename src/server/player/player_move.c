/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_move.c
*/

#include "player.h"

static bool	is_player_id(player_t *player, va_list *args)
{
	int	id = va_arg(*args, int);

	return player->id == id;
}

void	player_remove_from_map(player_t *self)
{
	if (self->pos && self->pos->players) {
		list_it_remove(self->pos->players,
			(list_it_fct_remove_t)is_player_id, self->id);
	}
}

void	player_move(player_t *self)
{
	player_move_toward(self, self->dir, 1);
}

void	player_move_to(player_t *self, point_t pos)
{
	player_remove_from_map(self);
	self->pos = map_content_at(self->map, pos);
	list_push_back(self->pos->players, self);
}

void	player_move_toward(player_t *self, direction_t dir, int inc)
{
	point_t	pos = map_move(self->map, self->pos->pos, dir, inc);

	player_remove_from_map(self);
	self->pos = map_content_at(self->map, pos);
	list_push_back(self->pos->players, self);
}
