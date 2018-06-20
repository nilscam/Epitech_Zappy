/*
** EPITECH PROJECT, 2018
** select
** File description:
** select
*/

#include "tcp_connection_client.h"

void	fill_fds(t_client *this)
{
	FD_ZERO(&this->_fds[READ_FDS]);
	FD_ZERO(&this->_fds[WRITE_FDS]);
	FD_ZERO(&this->_fds[ERR_FDS]);
	FD_SET(this->_fd_server, &this->_fds[READ_FDS]);
	FD_SET(this->_fd_server, &this->_fds[WRITE_FDS]);
	FD_SET(this->_fd_server, &this->_fds[ERR_FDS]);
}

int		get_max_fd(t_client *this)
{
	return (this->_fd_server + 1);
}

int		prepare_select(t_client *this, int timeout)
{
	int	max_fd = get_max_fd(this);

	fill_fds(this);
	struct timeval tv = {timeout, 0};
	return (select(max_fd, &this->_fds[READ_FDS], &this->_fds[WRITE_FDS],
			&this->_fds[ERR_FDS], &tv));
}