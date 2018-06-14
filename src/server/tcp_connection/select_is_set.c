/*
** EPITECH PROJECT, 2018
** select_is_set
** File description:
** select_is_set
*/

#include "tcp_connection.h"

int		can_read(t_server *this, int fd)
{
	return (FD_ISSET(fd, &this->_fds[READ_FDS]));
}

int		can_write(t_server *this, int fd)
{
	return (FD_ISSET(fd, &this->_fds[WRITE_FDS]));
}

int		can_err(t_server *this, int fd)
{
	return (FD_ISSET(fd, &this->_fds[ERR_FDS]));
}