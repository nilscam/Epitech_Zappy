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
	list_clear(server->anonymous, (void (*)(void *))client_delete);
	list_clear(server->spectators, (void (*)(void *))client_delete);
	SAFE_DELETE(server->anonymous);
	SAFE_DELETE(server->spectators);
	SAFE_DELETE(server->map);
	SAFE_FREE(server);
}
