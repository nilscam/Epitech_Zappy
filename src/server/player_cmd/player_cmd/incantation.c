/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_incantation(player_cmd_arg_t *args)
{
	client_callback(CB_ELEVATION_UNDERWAY, args->client);
}
