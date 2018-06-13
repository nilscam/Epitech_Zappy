/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_turn.c
*/

#include "player.h"

void	player_turn_left(player_t *self)
{
	self->dir = direction_turn_left(self->dir);
}

void	player_turn_right(player_t *self)
{
	self->dir = direction_turn_right(self->dir);
}
