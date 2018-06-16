/*
** EPITECH PROJECT, 2018
** clients_add
** File description:
** clients_add
*/

#include "tcp_connection.h"
#include "player_callback.h"

void	add_client(t_server *this)
{
	struct sockaddr_in	address;
	int			addrlen = sizeof(address);
	int			fd;
	client_t		*client;

	fd = accept(this->_fd_server,
		(struct sockaddr *)&address, (socklen_t*)&addrlen);
	if (fd < 0)
		return;
	DEBUG("New connection to fd %d\n", fd);
	client = client_new(fd, CLIENT_ANONYMOUS);
	if (client) {
		client_callback(CB_WELCOME, client);
		list_push_back(this->anonymous_clients, client);
	} else {
		close(fd);
	}
}
