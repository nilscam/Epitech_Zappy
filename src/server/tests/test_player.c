/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_player.c
*/

#include "player.h"
#include "map.h"
#include <string.h>
#include <stdio.h>

void	test_player_move(player_t *player);

static void	test_player_food(player_t *player)
{
	for (int i = 0; i < 200; ++i)
		player_consume_time(player);
	player_print(player);
	for (int i = 0; i < 20000; ++i)
		player_consume_time(player);
	player_print(player);
}

int	test_player(void)
{
	char		*team = strdup("Red");
	char		*name = strdup("Ash");
	map_t		*map = new(MAP, 3, 3);
	player_t	*player = NULL;

	if (!map)
		return 84;
	player = new(PLAYER, map, &map->cases[1][0], team, name);
	if (player) {
		test_player_move(player);
		test_player_food(player);
	}
	delete(player);
	delete(map);
	return 0;
}
