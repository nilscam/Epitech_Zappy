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

	fd = accept(this->_fd_server,
		(struct sockaddr *)&address, (socklen_t*)&addrlen);
	add_player_to_map(map, fd);
	DEBUG("New connection to fd %d\n", fd);
	
}
