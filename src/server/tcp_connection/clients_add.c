/*
** EPITECH PROJECT, 2018
** clients_add
** File description:
** clients_add
*/

#include "tcp_connection.h"

void	new_client(t_server *this, int fd)
{
	t_client	*new_client = malloc(sizeof(t_client));
	t_client	*tmp = this->_clients;

	new_client->_fd = fd;
	buff_init(&new_client->_cbuf, SIZE_BUFF);
	new_client->next = NULL;
	while (tmp && tmp->next) {
		tmp = tmp->next;
	}
	if (!tmp) {
		this->_clients = new_client;
	} else {
		tmp->next = new_client;
	}
}

void	add_client(t_server *this)
{
	struct sockaddr_in	address;
	int		addrlen = sizeof(address);
	int	fd;

	fd = accept(this->_fd_server, (struct sockaddr *)
				&address, (socklen_t*)&addrlen);
	new_client(this, fd);
}