/*
** EPITECH PROJECT, 2018
** clients_remove
** File description:
** clients_remove
*/

#include "server.h"

void	stop_server(t_server *this)
{
	DEBUG("stop_server");
	if (this->_fd_server >= 0) {
		close(this->_fd_server);
		this->_fd_server = -1;
	}
}