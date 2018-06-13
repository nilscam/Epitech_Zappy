/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_move.c
*/

#include "map.h"

bool	map_is_in_map(map_t *self, point_t pos)
{
	int	sx = self->size.x;
	int	sy = self->size.y;

	return !(pos.y < 0 || pos.y >= sy || pos.x < 0 || pos.x >= sx);
}

point_t	map_move(map_t *self, point_t from, direction_t to, int inc)
{
	point_t	pos = point_move(from, to, inc);

	if (pos.x < 0) {
		pos.x = self->size.x + (pos.x % self->size.x);
	}
	if (pos.y < 0) {
		pos.y = self->size.y + (pos.y % self->size.y);
	}
	pos.x = pos.x % self->size.x;
	pos.y = pos.y % self->size.y;
	return pos;
}
