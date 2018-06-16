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

static void	client_handle(t_server *server, client_t *client)
{
	char	*cmd;

	do {
		cmd = list_extract(client->read_buff, "\n");
		if (!cmd)
			break;
		if (*cmd) {
			DEBUG("cmd from %d: '%s'", client->_fd, cmd);
			client_cmd(server, client, cmd);
		}
		free(cmd);
	} while (cmd);
}

static bool	check_tcp_client(client_t *client, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);
	bool		remove_it = false;

	if (server->can_read(server, client->_fd)) {
		remove_it = !client_read(client);
		client_handle(server, client);
	}
	if (server->can_write(server, client->_fd)) {
		client_write(client);
	}
	if (remove_it) {
		DEBUG("removing client %d", client->_fd);
		if (client->type == CLIENT_PLAYER) {
			map_remove_player_with_fd(server->map, client->_fd);
		} else {
			client_delete(client);
		}
	}
	return remove_it;
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
