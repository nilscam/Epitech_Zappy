/*
** EPITECH PROJECT, 2018
** init_client
** File description:
** init_client
*/

#include "tcp_connection_client.h"

int		create_socket(char *protocol)
{
	struct protoent		*pe;

	pe = getprotobyname(protocol);
	if (!pe)
		return (-1);
	return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}

int		connect_socket(char *ip, int port, int fd)
{
	struct sockaddr_in	s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	return (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)));
}

int	init_client(t_client *this, char *ip, int port, char *protocol)
{
	int			fd;

	fd = create_socket(protocol);
	if (fd == -1 || connect_socket(ip, port, fd) == -1)
		return (-1);
	this->_fd_server = fd;
	return (fd);
}