/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_pos.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "map_it.h"

void	spectate_cmd_player_pos(player_cmd_arg_t *args)
{
	player_t	*player;

	player = get_player_from_id(args->server->map, atoi(args->args[1]));
	if (!player)
		return;
	client_callback(CB_PLAYER_POSITION, args->client,
		player->id,
		player->pos->pos.x,
		player->pos->pos.y,
		direction_to_int_spec(player->dir));
}
