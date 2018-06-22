/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_utils.c
*/

#include <utils/point.h>
#include "player.h"
#include "map_it.h"

player_t	*add_player_to_map(map_t *map,
	const team_t *team, client_t *client)
{
	point_t	pos;

	pos.y = rand() % map->size.y;
	pos.x = rand() % map->size.x;
	return (add_player_to_map_at(map, pos, team, client));
}

player_t	*add_player_to_map_at(map_t *map, point_t pos,
	const team_t *team, client_t *client)
{
	map_content_t	*c = map_content_at(map, pos);
	player_t 	*player;
	const char	*name = strdup("player");

	if (!name || !team)
		return NULL;
	player = NEW(PLAYER, map, c, team, name, client);
	if (!player || !list_push_back(map->players, player))
		return NULL;
	else if (!list_push_back(c->players, player)) {
		list_pop_back(map->players);
		return NULL;
	}
	return player;
}

map_content_t	*map_content_at(map_t *self, point_t pos)
{
	pos = map_move(self, pos, DIR_NONE, 0);

	return &self->cases[pos.y][pos.x];
}