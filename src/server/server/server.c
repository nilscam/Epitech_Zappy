/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "server.h"

int	create_socket(char *protocol)
{
	struct protoent		*pe;

	pe = getprotobyname(protocol);
	if (!pe)
		return (-1);
	return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}

int	bind_socket(int fd, int port)
{
	struct sockaddr_in	s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = INADDR_ANY;
	return (bind(fd, (const struct sockaddr *)&s_in, sizeof(s_in)));
}

int	listen_socket(int fd, int max_client)
{
	return (listen(fd, max_client));
}

int	init_server(t_server *this, int port, char *protocol)
{
	int			fd;

	fd = create_socket(protocol);
	if (fd == -1 ||
	bind_socket(fd, port) == -1 ||
	listen_socket(fd, MAX_CLIENT) == -1)
		return (-1);
	this->_fd_server = fd;
	return (fd);
}