/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_init.c
*/

#include "map.h"

static bool	init_map_content(map_content_t *self, point_t pos)
{
	self->pos = pos;
	init_map_inventory(&self->inventory);
	self->players = NEW(LIST_ALLOC, 10);
	return self->players != NULL;
}

bool	init_map_contents(map_t *self, int players_per_team, int nb_teams)
{
	(void)players_per_team;(void)nb_teams; //! tmp
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;

	for (int i = 0; i < size_y; ++i)
		self->cases[i] = self->cases_buff + size_x * i;
	self->cases[size_y] = NULL;
	for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			content = &self->cases[y][x];
			if (!init_map_content(content, (point_t){x, y}))
				return false;
		}
	}
	return true;
}
