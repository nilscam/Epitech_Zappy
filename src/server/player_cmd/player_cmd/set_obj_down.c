/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** set_obj_down.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	player_cmd_set_obj_down(player_cmd_arg_t *args)
{
	//todo set obj down
	client_callback(CB_OK, args->client);
}
