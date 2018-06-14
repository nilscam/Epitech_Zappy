/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** test_vision by Makrah
*/

#include <player/player.h>
#include "map_it.h"
#include "player.h"

int	test_vision()
{
	map_t*		map = NEW(MAP, 10, 10);
	player_t	*player = NULL;
	char		*team = strdup("Red");
	char		*name = strdup("Ash");

	printf("TESTING VISION\n");
	player = NEW(PLAYER, map, &map->cases[0][0], team, name, -1);
	add_player_to_map_at(map, (point_t){0, 0}, "Red", -1);
	add_player_to_map_at(map, (point_t){10, 1}, "Red", -1);

	player->dir = DIR_LEFT;
	printf("LVL1\n%s\n", look(map, player));
	player->level = 2;
	printf("LVL2\n%s\n", look(map, player));
	player->level = 3;
	printf("LVL3\n%s\n", look(map, player));
	player->level = 4;
	printf("LVL3\n%s\n", look(map, player));
	SAFE_DELETE(player);
	SAFE_DELETE(map);
	return (0);
}