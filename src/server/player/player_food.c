/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_food.c
*/

#include "player.h"

bool	player_is_dead_of_hunger(player_t *self)
{
	return self->inventory.food <= 0 && self->remaining_time_units <= 0;
}

void	player_consume_food(player_t *self)
{
	if (self->inventory.food > 0) {
		--self->inventory.food;
		self->remaining_time_units = FOOD_TO_TIME_UNITS;
	}
}

void	player_consume_time(player_t *self)
{
	if (self->remaining_time_units <= 0) {
		player_consume_food(self);
	}
	if (self->remaining_time_units > 0) {
		--self->remaining_time_units;
	}
}
