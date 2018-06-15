/*
** EPITECH PROJECT, 2018
** clients_add
** File description:
** clients_add
*/

#include "tcp_connection.h"

void	add_client(t_server *this, map_t *map)
{
	struct sockaddr_in	address;
	int			addrlen = sizeof(address);
	int			fd;
	client_t		*client;

	fd = accept(this->_fd_server,
		(struct sockaddr *)&address, (socklen_t*)&addrlen);
	client = client_new(fd, false);
	if (client) {
		add_player_to_map(map, client);
	}
	DEBUG("New connection to fd %d\n", fd);
	
}
