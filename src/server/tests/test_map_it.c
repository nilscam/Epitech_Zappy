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
	int		players_per_team = 12;
	int		nb_teams = 2;
	map_t		*map = NEW(MAP, 2, 2, players_per_team, nb_teams);
	team_t		*red_team = team_new(strdup("red"), 12);
	team_t		*blue_team = team_new(strdup("blue"), 12);

	if (!map)
		return (84);
	add_player_to_map_at(map, (point_t){1, 1}, red_team, NULL);
	add_player_to_map_at(map, (point_t){0, 0}, red_team, NULL);
	add_player_to_map_at(map, (point_t){1, 1}, red_team, NULL);
	add_player_to_map_at(map, (point_t){1, 1}, blue_team, NULL);
	printf("all players:\n");
	list_it_all(map->players, (list_it_fct_t)show_player_fct);
	printf("\nall players at (1,1):\n");
	map_it_players_at(map, (point_t){1, 1}, show_player_fct);
	if (!map_it_players_at(map, (point_t){1, 0}, show_player_fct)) {
		printf("\nthere is no player at (1,0)\n");
	}
	list_clear(map->players, delete_class);
	DELETE(map);
	team_delete(red_team);
	team_delete(blue_team);
	return 0;
}
