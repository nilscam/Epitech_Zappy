/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** left.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_left(player_cmd_arg_t *args)
{
	player_turn_left(args->player);
	client_callback(CB_OK, args->client);
}
