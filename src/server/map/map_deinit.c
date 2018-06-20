/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_deinit.c
*/

#include "map.h"

static void	deinit_map_content(map_content_t *self)
{
	SAFE_DELETE(self->players);
}

void	deinit_map_contents(map_t *self)
{
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;

	for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			content = &self->cases[y][x];
			deinit_map_content(content);
		}
	}
}
