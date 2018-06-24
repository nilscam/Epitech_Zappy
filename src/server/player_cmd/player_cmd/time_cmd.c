/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** time_cmd.c
*/

#include "player_cmd.h"
#include "player_callback.h"

void	spectate_cmd_time(player_cmd_arg_t *args)
{
	client_callback(CB_TIME, args->client, args->server->turn);
}
