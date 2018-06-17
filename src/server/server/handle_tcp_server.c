/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_tcp_server.c
*/

#include "server.h"

void	handle_tcp_server(t_server *server)
{
	if (server->can_read(server, server->_fd_server)) {
		server->add_client(server);
	}
}
