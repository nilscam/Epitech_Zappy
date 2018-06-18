/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_init.c
*/

#include "map.h"

static void init_map_content(map_content_t *content, point_t pos, map_t *map)
{
	content->pos = pos;
	init_map_inventory(&content->inventory, map);
}

void	init_map_contents(map_t *self)
{
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;

	for (int i = 0; i < size_y; ++i)
		self->cases[i] = self->cases_buff + size_x * i;
	self->cases[size_y] = NULL;
	for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			content = &self->cases[y][x];
			init_map_content(content, (point_t){x, y}, self);
		}
	}
}
