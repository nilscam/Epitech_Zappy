/*
** EPITECH PROJECT, 2018
** main_test
** File description:
** main
*/

#include "tcp_connection.h"
#include "player.h"
#include "save_signal.h"
#include "player_cmd.h"

int		read_client_data(t_server *server, client_t *client)
{
	char	buff[SIZE_BUFF];

	(void)server;
	int ret = read(client->_fd, buff, SIZE_BUFF - 1);
	if  (ret <= 0) {
		return (0);
	}
	buff[ret] = 0;
	buff_put(&client->_cbuf, buff);
	if (buff[ret - 1] == '\n') {
		char *str = buff_get(&client->_cbuf);
		printf("[%s]\n", str);
		if (!player_cmd(str)) {
			DEBUG("ko");
		}
	}
	return (1);
}

static bool	check_tcp_client(client_t *client, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);

	if (server->can_read(server, client->_fd)) {
		DEBUG("can_read from %d", client->_fd);
		if (!read_client_data(server, client)) {
			DEBUG("remove client from %d", client->_fd);
			if (client->type == CLIENT_PLAYER) {
				DEBUG("removing player..");
				// todo remove player from map
			}
			return true;
		}
	}
	if (server->can_write(server, client->_fd)) {
		// todo write to buff
	}
	return false;
}

static void	check_tcp_clients(t_server *server)
{
	list_it_fct_remove_t fct = (list_it_fct_remove_t)check_tcp_client;

	list_it_remove(server->anonymous, fct, server);
	list_it_remove(server->spectators, fct, server);
	list_it_remove(server->players, fct, server);
}

int	test_tcp_connection(int ac, char **av)
{
	map_t		*map = NEW(MAP, 10, 10);
	t_server	*server = init_struct_server(map->players, map);

	if (!server || ac != 2 || !map)
		return (84);
	setup_signals(server);
	int	port = atoi(av[1]);
	if (server->init(server, port, "TCP") == -1)
		return (84);
	while (1) {
		server->select(server, TIMEOUT);
		check_tcp_clients(server);
		if (server->can_read(server, server->_fd_server)) {
			server->add_client(server);
		}
	}
	deinit_server(server);
	return (0);
}