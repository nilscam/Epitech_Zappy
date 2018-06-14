/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_move.c
*/

#include "player.h"

void	player_move(player_t *self)
{
	player_move_toward(self, self->dir, 1);
}

void	player_move_to(player_t *self, point_t pos)
{
	self->pos = map_content_at(self->map, pos);
}

void	player_move_toward(player_t *self, direction_t dir, int inc)
{
	point_t	pos = map_move(self->map, self->pos->pos, dir, inc);

	self->pos = map_content_at(self->map, pos);
}
