/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** forward.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_forward(player_cmd_arg_t *args)
{
	player_move(args->player);
	client_callback(CB_OK, args->client);
	clients_callback(CB_PLAYER_POSITION,
		args->server->spectators_clients,
		args->player->id,
		args->player->pos->pos.x,
		args->player->pos->pos.y,
		direction_to_int_spec(args->player->dir));
}
