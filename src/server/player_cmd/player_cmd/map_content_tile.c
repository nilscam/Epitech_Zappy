/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_content_tile.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_map_content_tile(player_cmd_arg_t *args)
{
	point_t	point = { atoi(args->args[0]), atoi(args->args[1]) };
	map_content_t *c = map_content_at(args->server->map, point);

	client_callback(CB_CONTENT_TILE, args->client,
		point.x, point.y,
		c->inventory.food,
		c->inventory.stones[LINEMATE],
		c->inventory.stones[DERAUMERE],
		c->inventory.stones[SIBUR],
		c->inventory.stones[MENDIANE],
		c->inventory.stones[PHIRAS],
		c->inventory.stones[THYSTAME]);
}
