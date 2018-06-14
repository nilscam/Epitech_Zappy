/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** test_vision by Makrah
*/

#include <player/player.h>
#include "map.h"
#include "player.h"

int	test_vision()
{
	map_t*		map = NEW(MAP, 10, 10);
	player_t	*player = NULL;
	char		*team = strdup("Red");
	char		*name = strdup("Ash");

	player = NEW(PLAYER, map, &map->cases[1][0], team, name);
	player->dir = DIR_LEFT;
	look(map, player);
	return (0);
}