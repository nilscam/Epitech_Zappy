/*
** EPITECH PROJECT, 2018
** clients_remove
** File description:
** clients_remove
*/

#include "tcp_connection.h"

void	remove_client(t_server *this, int fd)
{
	t_client	*tmp_a = this->_clients, *tmp_b = NULL;

	if (tmp_a->next)
		tmp_b = tmp_a->next;
	if (tmp_a->_fd == fd) {
		this->_clients = tmp_a->next;
		return;
	}
	while (tmp_b && tmp_b->_fd != fd) {
		tmp_a = tmp_a->next;
		tmp_b = tmp_b->next;
	}
	if (tmp_b) {
		tmp_a->next = tmp_b->next;
		free(tmp_b);
	} else {
		free(tmp_a);
		this->_clients = NULL;
	}
}

void	close_client(t_server *this, int fd)
{
	close(fd);
	remove_client(this, fd);
}

void	stop_server(t_server *this)
{
	t_client	*tmp = this->_clients;

	if (this->_fd_server == -1)
		return;
	while (this->_clients) {
		close_client(this, this->_clients->_fd);
	}
	close(this->_fd_server);
}