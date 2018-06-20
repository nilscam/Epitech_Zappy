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
	int		players_per_team = 12;
	int		nb_teams = 2;
	map_t*		map = NEW(MAP, 25, 25, players_per_team, nb_teams);
	player_t	*player = NULL;
	team_t		*team = team_new("Red", 12);
	char		*name = strdup("Ash");

//	printf("TESTING VISION\n");
	player = NEW(PLAYER, map, &map->cases[2][2], team, name, NULL);
	add_player_to_map_at(map, (point_t){2, 2}, team, NULL);
//	add_player_to_map_at(map, (point_t){10, 1}, "Red", NULL);

	player->dir = DIR_LEFT;
	player->level = 8;
	printf("LVL1 - Looking left\n%s\n", look(map, player));
/*	player->dir = DIR_RIGHT;
	printf("LVL1 - Looking right\n%s\n", look(map, player));
	player->dir = DIR_DOWN;
	printf("LVL1 - Looking down\n%s\n", look(map, player));*/
/*	player->dir = DIR_UP;
	printf("LVL1 - Looking up\n%s\n", look(map, player));
	player->level = 2;
	printf("LVL2 - looking up\n%s\n", look(map, player));
	player->level = 3;
	printf("LVL3\n%s\n", look(map, player));
	player->level = 4;
	printf("LVL3\n%s\n", look(map, player));*/
	SAFE_DELETE(player);
	SAFE_DELETE(map);
	return (0);
}