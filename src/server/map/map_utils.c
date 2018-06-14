/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_utils.c
*/

#include <utils/point.h>
#include "player.h"
#include "map.h"

bool	add_player_to_map(map_t *map, const char *team, const char *name)
{
	point_t	pos;

	pos.y = rand() % map->size.y;
	pos.x = rand() % map->size.x;
	return (add_player_to_map_at(map, pos, team, name));
}

bool	add_player_to_map_at(map_t *map, point_t pos, const char *team,
	const char *name)
{
	map_content_t	*c = map_content_at(map, pos);
	player_t 	*player;

	team = strdup(team);
	name = strdup(name);
	if (!team || !name)
		return false;
	player = NEW(PLAYER, map, c, team, name);
	if (!player)
		return false;
	return list_push_back(map->players, player);
}

map_content_t	*map_content_at(map_t *self, point_t pos)
{
	pos = map_move(self, pos, DIR_NONE, 0);

	return &self->cases[pos.y][pos.x];
}