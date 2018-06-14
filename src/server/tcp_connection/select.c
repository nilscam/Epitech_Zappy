/*
** EPITECH PROJECT, 2018
** select
** File description:
** select
*/

#include "tcp_connection.h"

void	fill_fds(t_server *this)
{
	t_client	*tmp = this->_clients;

	FD_ZERO(&this->_fds[READ_FDS]);
	FD_ZERO(&this->_fds[WRITE_FDS]);
	FD_ZERO(&this->_fds[ERR_FDS]);
	FD_SET(this->_fd_server, &this->_fds[READ_FDS]);
	FD_SET(this->_fd_server, &this->_fds[WRITE_FDS]);
	FD_SET(this->_fd_server, &this->_fds[ERR_FDS]);
	while (tmp) {
		FD_SET(tmp->_fd, &this->_fds[READ_FDS]);
		FD_SET(tmp->_fd, &this->_fds[WRITE_FDS]);
		FD_SET(tmp->_fd, &this->_fds[ERR_FDS]);
		tmp = tmp->next;
	}
}

int		get_max_fd(t_server *this)
{
	t_client	*tmp = this->_clients;
	int			max_fd = this->_fd_server;

	while (tmp) {
		if (max_fd < tmp->_fd)
			max_fd = tmp->_fd;
		tmp = tmp->next;
	}
	return (max_fd + 1);
}

int		prepare_select(t_server *this, int timeout)
{
	int	max_fd = get_max_fd(this);

	fill_fds(this);
	struct timeval tv = {timeout, 0};
	return (select(max_fd, &this->_fds[READ_FDS], &this->_fds[WRITE_FDS],
			&this->_fds[ERR_FDS], &tv));
}