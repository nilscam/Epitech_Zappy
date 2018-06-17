/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_inventory(player_cmd_arg_t *args)
{
	client_callback(CB_PLAYER_INVENTORY, args->client,
		args->player->inventory.food,
		args->player->inventory.stones[LINEMATE],
		args->player->inventory.stones[DERAUMERE],
		args->player->inventory.stones[SIBUR],
		args->player->inventory.stones[MENDIANE],
		args->player->inventory.stones[PHIRAS],
		args->player->inventory.stones[THYSTAME]);
}
