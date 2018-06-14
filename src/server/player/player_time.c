/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_time.c
*/

#include "player.h"

void	player_wait_for(player_t *self, int time_units)
{
	self->is_busy_time_units += time_units;
}

void	player_set_is_busy_callback(player_t *self,
	pl_callback_t callback, void *args)
{
	self->is_busy_callback_args = args;
	self->is_busy_callback = callback;
}

void	player_wait(player_t *self)
{
	if (self->is_busy_time_units > 0)
		--self->is_busy_time_units;
	if (self->is_busy_time_units <= 0 && self->is_busy_callback) {
		self->is_busy_callback(self->is_busy_callback_args);
		self->is_busy_callback = NULL;
		self->is_busy_callback_args = NULL;
	}
}

bool	player_is_busy(player_t *self)
{
	return self->is_busy_time_units > 0;
}
