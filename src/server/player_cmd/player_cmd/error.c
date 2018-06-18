/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** error.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_error(player_cmd_arg_t *args)
{
	client_callback(CB_UNKNOWN_COMMAND, args->client);
}

void	player_cmd_error(player_cmd_arg_t *args)
{
	client_callback(CB_KO, args->client);
}
