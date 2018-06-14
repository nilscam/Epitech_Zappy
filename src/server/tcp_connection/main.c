/*
** EPITECH PROJECT, 2018
** main_test
** File description:
** main
*/

#include "tcp_connection.h"

int		main(int ac, char **av)
{
	t_server	*server = init_struct_server();

	if (!server || ac != 2)
		return (84);
	int	port = atoi(av[1]);
	server->init(server, port, "TCP");
	while (1) {
		server->select(server, 1);
		for (t_client *tmp = server->_clients; tmp; tmp = tmp->next) {
			if (server->can_read(server, tmp->_fd)) {}
			if (server->can_write(server, tmp->_fd)) {}
			if (server->can_err(server, tmp->_fd)) {}
		}
		if (server->can_read(server, server->_fd_server)) {
			server->add_client(server);
		}
	}
	return (0);
}