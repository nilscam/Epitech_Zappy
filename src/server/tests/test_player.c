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
#include <stdint.h>

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

static void	player_time_callback(int arg)
{
	printf("player_time_callback %d\n", arg);
}

static void	test_player_time(player_t *player)
{
	int	callback_arg = 42;

	printf("test_player_time before\n");
	player_wait_for(player, 7);
	player_set_is_busy_callback(player,
		(pl_callback_t)player_time_callback,
		(void *)(intptr_t)callback_arg);
	while (player_is_busy(player))
		player_wait(player);
	player_wait(player);
	printf("test_player_time after\n");
}

int	test_player(void)
{
	team_t		*team = team_new("Red", 12);
	char		*name = strdup("Ash");
	int		players_per_team = 12;
	map_t		*map = NEW(MAP, 3, 3, players_per_team);
	player_t	*player = NULL;

	if (!map)
		return 84;
	player = NEW(PLAYER, map, &map->cases[1][0], team, name, NULL);
	if (player) {
		test_player_move(player);
		test_player_time(player);
		test_player_food(player);
	}
	SAFE_DELETE(player);
	SAFE_DELETE(map);
	team_delete(team);
	return 0;
}
