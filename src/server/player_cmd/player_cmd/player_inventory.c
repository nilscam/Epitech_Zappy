/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_inventory.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "map_it.h"

void	spectate_cmd_player_inventory(player_cmd_arg_t *args)
{
	player_t	*player;

	player = get_player_from_id(args->server->map, atoi(args->args[1]));
	if (!player)
		return;
	client_callback(CB_PLAYER_INVENTORY, args->client,
		player->id,
		player->pos->pos.x,
		player->pos->pos.y,
		player->inventory.food,
		player->inventory.stones[LINEMATE],
		player->inventory.stones[DERAUMERE],
		player->inventory.stones[SIBUR],
		player->inventory.stones[MENDIANE],
		player->inventory.stones[PHIRAS],
		player->inventory.stones[THYSTAME]);
}
