/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** food.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "math_utils.h"

void	spectate_cmd_food(player_cmd_arg_t *args)
{
	map_content_t	*content;
	inventory_t	*inv;
	int	food = atoi(args->args[1]);
	int	size_x = args->server->map->size.x;
	int	size_y = args->server->map->size.y;

	if (food <= 0) {
		client_callback(CB_KO, args->client);
		return;
	}
	client_callback(CB_OK, args->client);
	for (int y = 0; y < size_y ; ++y) {
		for (int x = 0; x < size_x ; ++x) {
			content = &args->server->map->cases[y][x];
			inv = &content->inventory;
			inv->food += randome_between(0, food);
		}
	}
	spectate_cmd_content_map(args);
}
