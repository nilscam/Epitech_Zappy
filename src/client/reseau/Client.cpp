/*
** EPITECH PROJECT, 2018
** Client
** File description:
** Client
*/

#include "Client.hpp"

Client::Client()
	:	_fd_server(-1)
{}

Client::~Client()
{
	this->disconnect();
}

int			Client::connectServer(const char *ip, int port)
{
	int			fd;

	this->disconnect();
	fd = this->create_socket();
	if (fd == -1 || this->connect_socket(ip, port, fd) == -1)
		return (-1);
	this->_fd_server = fd;
	return (fd);
}
void		Client::disconnect(void)
{
	if (_fd_server != -1) {
		close(_fd_server);
	}
	_fd_server = -1;
}
bool		Client::isConnected(void) const
{
	return (_fd_server != -1);
}
int			Client::getFdServer(void) const
{
	return (_fd_server);
}

int			Client::connect_socket(const char *ip, int port, int fd)
{
	struct sockaddr_in	s_in;

	s_in.sin_family = AF_INET;
	s_in.sin_port = htons(port);
	s_in.sin_addr.s_addr = inet_addr(ip);
	return (connect(fd, (struct sockaddr *)&s_in, sizeof(s_in)));
}

int			Client::create_socket()
{
	struct protoent		*pe;

	pe = getprotobyname("TCP");
	if (!pe)
		return (-1);
	return (socket(AF_INET, SOCK_STREAM, pe->p_proto));
}