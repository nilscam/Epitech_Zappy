/*
** EPITECH PROJECT, 2018
** Client
** File description:
** Client
*/

#ifndef CLIENT_HPP_
# define CLIENT_HPP_

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

class Client
{
public:
	Client() = default;
	virtual ~Client() = default;

	int			connect(char *ip, int port, char *protocol);
	void		disconnect(void);
	bool		isConnected(void) const;
	int			getFdServer(void) const;
private:
	int			connect_socket(char *ip, int port, int fd);
	int			create_socket(char *protocol);
	int			_fd_server;
};

#endif	/* CLIENT_HPP_ */