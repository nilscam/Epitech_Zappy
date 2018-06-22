/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** time_unit.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_time_unit(player_cmd_arg_t *args)
{
	client_callback(CB_TIME_UNIT_REQUEST, args->client,
		(int)args->server->f);
}
