/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eject.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

bool	validate_eject(player_cmd_arg_t *args)
{
	//todo validate
	(void)args;
	client_callback(CB_KO, args->client);
	return false;
}

void	player_cmd_eject(player_cmd_arg_t *args)
{
	//todo eject
	client_callback(CB_OK, args->client);
}
