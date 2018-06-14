/*
** EPITECH PROJECT, 2018
** clients_remove
** File description:
** clients_remove
*/

#include "tcp_connection.h"

void	stop_server(t_server *this)
{
	if (this->_fd_server == -1)
		return;
	DEBUG("stop_server");
	list_clear(this->players, (void (*)(void *))delete_class);
	close(this->_fd_server);
}