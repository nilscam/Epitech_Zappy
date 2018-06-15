/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** deinit.c
*/

#include "tcp_connection.h"

void	deinit_server(t_server *server)
{
	if (!server)
		return;
	server->stop(server);
	list_clear(server->players, (void (*)(void *))delete_class);
	list_clear(server->spectators, (void (*)(void *))free);
	SAFE_DELETE(server->spectators);
	SAFE_DELETE(server->map);
	SAFE_FREE(server);
}
