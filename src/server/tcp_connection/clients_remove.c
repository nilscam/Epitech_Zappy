/*
** EPITECH PROJECT, 2018
** clients_remove
** File description:
** clients_remove
*/

#include "tcp_connection.h"

t_client	*remove_exist_client(t_server *this,
								t_client *tmp_a, t_client *tmp_b)
{
	if (tmp_b) {
		tmp_a->next = tmp_b->next;
		free(tmp_b);
		return (tmp_a->next);
	} else {
		free(tmp_a);
		this->_clients = NULL;
		return (NULL);
	}
}

t_client	*remove_client(t_server *this, int fd)
{
	t_client	*tmp_a = this->_clients, *tmp_b = NULL;

	if (tmp_a->next)
		tmp_b = tmp_a->next;
	if (tmp_a->_fd == fd) {
		tmp_a = tmp_a->next;
		free(this->_clients);
		this->_clients = tmp_a;
		return (tmp_a);
	}
	while (tmp_b && tmp_b->_fd != fd) {
		tmp_a = tmp_a->next;
		tmp_b = tmp_b->next;
	}
	return (remove_exist_client(this, tmp_a, tmp_b));
}

t_client	*close_client(t_server *this, int fd)
{
	printf("Close Connection\n");
	close(fd);
	return (remove_client(this, fd));
}

void	stop_server(t_server *this)
{
	if (this->_fd_server == -1)
		return;
	while (this->_clients) {
		close_client(this, this->_clients->_fd);
	}
	close(this->_fd_server);
}