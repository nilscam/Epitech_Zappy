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
#include <unistd.h>

class Client
{
public:
	Client() = default;
	virtual ~Client() = default;

	int			connectServer(const char *ip, int port);
	void		disconnect(void);
	bool		isConnected(void) const;
	int			getFdServer(void) const;
private:
	int			connect_socket(const char *ip, int port, int fd);
	int			create_socket(void);
	int			_fd_server;
};

#endif	/* CLIENT_HPP_ */