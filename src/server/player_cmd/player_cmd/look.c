/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** look.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "map_it.h"

void	player_cmd_look(player_cmd_arg_t *args)
{
	char *vision = look(args->server->map, args->player);

	list_push_back(args->client->write_buff, vision);
}
