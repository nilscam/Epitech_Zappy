/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_init.c
*/

#include <utils/math_utils.h>
#include "map.h"

static bool	init_map_content(map_content_t *self, point_t pos,
	inventory_t* inv)
{
	self->pos = pos;
	init_map_inventory(&self->inventory, inv);
	self->players = NEW(LIST_ALLOC, 10);
	return self->players != NULL;
}

/*
max = [REQUIS] * [rand entre 1 et nb_max_joueurs] * nb_teams
to_place = rand(max / 2, max)
*/

void	init_total_map_content(inventory_t *inv,int players, int nb_teams,
	map_t *map)
{
	inv->stones[0] = 33 * players * nb_teams * 0;
	inv->stones[1] = 38 * players * nb_teams * 0;
	inv->stones[2] = 46 * players * nb_teams * 0;
	inv->stones[3] = 24 * players * nb_teams * 0;
	inv->stones[4] = 26 * players * nb_teams * 0;
	inv->stones[5] = 6 * players * nb_teams * 0;
	inv->food = map->size.x * map->size.y * randome_between(1, 4) +200;
}

bool	not_empty(inventory_t *inv)
{
	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
		if (inv->stones[i] > 1)
			return true;
	}
	if (inv->food > 1)
		return true;
	return false;
}

bool	init_map_contents(map_t *self, int players_per_team, int nb_teams)
{
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;
	inventory_t inv;

	init_total_map_content(&inv, players_per_team, nb_teams, self);
	for (int i = 0; i < size_y; ++i)
		self->cases[i] = self->cases_buff + size_x * i;
	self->cases[size_y] = NULL;
	while (not_empty(&inv)) {
		for (int y = 0; y < size_y ; ++y) {
			for (int x = 0; x < size_x ; ++x) {
				content = &self->cases[y][x];
				if (!init_map_content(content, (point_t){x, y},
					&inv))
					return false;
			}
		}
	}
	return true;
}
