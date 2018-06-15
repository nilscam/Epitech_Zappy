/*
** EPITECH PROJECT, 2018
** select
** File description:
** select
*/

#include "tcp_connection.h"
#include "player.h"
#include "map_it.h"

static void	set_client_fd_set(client_t *client, va_list *args)
{
	fd_set	*fds = va_arg(*args, fd_set *);
	int	*max_fd = va_arg(*args, int *);

	if (*max_fd < client->_fd) {
		*max_fd = client->_fd;
	}
	FD_SET(client->_fd, &fds[READ_FDS]);
	FD_SET(client->_fd, &fds[WRITE_FDS]);
	FD_SET(client->_fd, &fds[ERR_FDS]);
}

static void	fill_fds(t_server *this, int *max_fd)
{
	list_it_fct_t	fct = (list_it_fct_t)set_client_fd_set;

	FD_ZERO(&this->_fds[READ_FDS]);
	FD_ZERO(&this->_fds[WRITE_FDS]);
	FD_ZERO(&this->_fds[ERR_FDS]);
	*max_fd = this->_fd_server;
	FD_SET(this->_fd_server, &this->_fds[READ_FDS]);
	FD_SET(this->_fd_server, &this->_fds[WRITE_FDS]);
	FD_SET(this->_fd_server, &this->_fds[ERR_FDS]);
	list_it_all(this->anonymous, fct, this->_fds, max_fd);
	list_it_all(this->players, fct, this->_fds, max_fd);
	list_it_all(this->spectators, fct, this->_fds, max_fd);
	*max_fd += 1;
}

int		prepare_select(t_server *this, int timeout)
{
	int	max_fd = -1;

	fill_fds(this, &max_fd);
	if (max_fd < 0)
		return -1;
	struct timeval tv = { timeout, 0 };
	return (select(max_fd, &this->_fds[READ_FDS], &this->_fds[WRITE_FDS],
			&this->_fds[ERR_FDS], &tv));
}