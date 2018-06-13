/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_player.c
*/

#include "player.h"
#include "map.h"
#include <string.h>

int	test_player(void)
{
	char		*team = strdup("Red");
	char		*name = strdup("Ash");
	map_t		*map = new(MAP, 3, 3);
	player_t	*player = NULL;

	if (map) {
		player = new(PLAYER, map, &map->cases[1][0], team, name);
		if (player) {
			player_print(player);
		}
	}
	delete(player);
	delete(map);
	return 0;
}
