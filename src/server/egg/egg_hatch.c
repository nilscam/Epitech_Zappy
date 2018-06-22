/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** egg_hatch.c
*/

#include "egg.h"

void	egg_wait(egg_t *self)
{
	if (self->remaining_time_units > 0) {
		--self->remaining_time_units;
	}
}

bool	egg_is_hatched(egg_t *self)
{
	return self->remaining_time_units <= 0;
}

bool	egg_will_hatch(egg_t *self)
{
	return self->remaining_time_units == 1;
}
