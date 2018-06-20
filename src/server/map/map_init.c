/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_init.c
*/

#include "map.h"

static void init_map_content(map_content_t *content, point_t pos)
{
	content->pos = pos;
	init_map_inventory(&content->inventory);
}
/*
max = [REQUIS] * [rand entre 1 et nb_max_joueurs] * nb_teams
	to_place = rand(max / 2, max)
*/

void	init_map_contents(map_t *self, int players_per_team, int nb_teams)
{
	(void)players_per_team;(void)nb_teams; //! tmp
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;
	inventory_t inv;

	inv.stones[0] = 198;
	inv.stones[1] = 228;
	inv.stones[2] = 276;
	inv.stones[3] = 144;
	inv.stones[4] = 156;
	inv.stones[5] = 36;
	for (int i = 0; i < size_y; ++i)
		self->cases[i] = self->cases_buff + size_x * i;
	self->cases[size_y] = NULL;
	for (int y = 0; y < size_y ; ++y) {
		for (int x = 0; x < size_x; ++x) {
			content = &self->cases[y][x];
			init_map_content(content, (point_t){x, y});
		}
	}
}
