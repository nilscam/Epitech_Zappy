/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** anonymous_cmd_spectator.c
*/

#include "player_cmd.h"
#include "player_callback.h"

void	anonymous_cmd_spectator(player_cmd_arg_t *args)
{
	t_server	*server = args->server;
	client_t	*client = args->client;

	client_callback(CB_WELCOME_SPECTATOR, client);
	client->type = CLIENT_SPECTATOR;
	list_push_back(server->spectators_clients, client);
}
