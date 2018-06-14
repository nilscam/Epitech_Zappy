/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_map_it.c
*/

#include "map_it.h"
#include <stdio.h>

static void	show_player(player_t *player)
{
	player_print(player);
}

int	test_map_it(void)
{
	map_it_pl_t	show_player_fct = (map_it_pl_t)show_player;
	map_t		*map = NEW(MAP, 2, 2);

	if (!map)
		return (84);
	add_player_to_map(map, (point_t){1, 1}, "red", "Ash Ketchum");
	add_player_to_map(map, (point_t){0, 0}, "red", "Brock");
	add_player_to_map(map, (point_t){1, 1}, "red", "Misty Williams");
	add_player_to_map(map, (point_t){1, 1}, "blue", "Gary Oak");
	printf("all players:\n");
	map_it_players(map, show_player_fct);
	printf("\nall players at (1,1):\n");
	map_it_players_at(map, (point_t){1, 1}, show_player_fct);
	printf("\nall players in team blue:\n");
	map_it_players_team(map, "blue", show_player_fct);
	if (!map_it_players_at(map, (point_t){1, 0}, show_player_fct)) {
		printf("\nthere is no player at (1,0)\n");
	}
	list_clear(map->players, (void (*)(void *))delete_class);
	DELETE(map);
	return 0;
}
