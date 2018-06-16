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
	list_clear(server->anonymous_clients,
		(void (*)(void *))client_delete);
	list_clear(server->players_clients,
		(void (*)(void *))client_delete);
	list_clear(server->spectators_clients,
		(void (*)(void *))client_delete);
	list_clear(server->teams,
		(void (*)(void *))team_delete);
	SAFE_DELETE(server->anonymous_clients);
	SAFE_DELETE(server->players_clients);
	SAFE_DELETE(server->spectators_clients);
	SAFE_DELETE(server->teams);
	SAFE_DELETE(server->map);
	SAFE_FREE(server);
}
