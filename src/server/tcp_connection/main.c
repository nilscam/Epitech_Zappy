/*
** EPITECH PROJECT, 2018
** main_test
** File description:
** main
*/

#include "tcp_connection.h"

#include <signal.h>
void	handler(int sig)
{
	(void)sig;
	exit(0);
}

int		read_data(t_server *server, t_client *tmp)
{
	char	buff[SIZE_BUFF];

	(void)server;
	int ret = read(tmp->_fd, buff, SIZE_BUFF - 1);
	if  (ret <= 0) {
		return (0);
	}
	buff[ret] = 0;
	buff_put(&tmp->_cbuf, buff);
	if (buff[ret - 1] == '\n') {
		char *str = buff_get(&tmp->_cbuf);
		printf("[%s]\n", str);
	}
	return (1);
}

int		main(int ac, char **av)
{
	t_server	*server = init_struct_server();

	if (!server || ac != 2)
		return (84);
	int	port = atoi(av[1]);
	if (server->init(server, port, "TCP") == -1)
		return (84);
	signal(SIGINT, handler);
	while (1) {
		server->select(server, 1);
		for (t_client *tmp = server->_clients; tmp;) {
			if (server->can_read(server, tmp->_fd)) {
				if (!read_data(server, tmp)) {
					tmp = server->close_client(server, tmp->_fd);
					continue;
				}
			}
			if (tmp && server->can_write(server, tmp->_fd)) {}
			if (tmp && server->can_err(server, tmp->_fd)) {}
			tmp = tmp->next;
		}
		if (server->can_read(server, server->_fd_server)) {
			server->add_client(server);
		}
	}
	server->stop(server);
	return (0);
}