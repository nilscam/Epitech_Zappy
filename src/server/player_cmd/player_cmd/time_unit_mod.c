/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** time_unit_mod.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_time_unit_mod(player_cmd_arg_t *args)
{
	//todo replace time unit + change time unit
	client_callback(CB_TIME_UNIT_REQUEST, args->client, 1);
}
