/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** connect_nbr.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_connect_nbr(player_cmd_arg_t *args)
{
	client_callback(CB_NB_UNUSED_SLOTS, args->client,
		team_available_players((team_t *)args->player->team));
}
