/*
** EPITECH PROJECT, 2018
** stop_client
** File description:
** stop_client
*/

#include "tcp_connection_client.h"

void	stop_client(t_client *this)
{
	close(this->_fd_server);
}