/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** take.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_take(player_cmd_arg_t *args)
{
	//todo take object
	client_callback(CB_OK, args->client);
}
