/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_broadcast(player_cmd_arg_t *args)
{
	//todo broadcast
	client_callback(CB_OK, args->client);
}
