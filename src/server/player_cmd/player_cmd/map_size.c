/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_size.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_map_size(player_cmd_arg_t *args)
{
	client_callback(CB_MAP_SIZE, args->client,
		args->server->map->size.x, args->server->map->size.y);
}
