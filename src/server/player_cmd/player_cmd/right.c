/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** right.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_right(player_cmd_arg_t *args)
{
	player_turn_right(args->player);
	client_callback(CB_OK, args->client);
}