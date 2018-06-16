/*
** EPITECH PROJECT, 2018
** main_test
** File description:
** main
*/

#include "server.h"
#include "player.h"
#include "save_signal.h"
#include "player_cmd.h"

static bool	client_handle(t_server *server, client_t *client, player_t *player)
{
	char		*cmd;
	client_type_t	type;
	bool		remove_it = false;

	do {
		cmd = list_extract(client->read_buff, "\n");
		if (!cmd)
			break;
		if (*cmd) {
			DEBUG("cmd from %d: '%s'", client->_fd, cmd);
			type = client->type;
			client_cmd(server, client, cmd, player);
			if (type != client->type) {
				remove_it = true;
			}
		}
		free(cmd);
	} while (cmd && !remove_it);
	return remove_it;
}

static bool	check_tcp_client(client_t *client, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);

	if (server->can_read(server, client->_fd)) {
		if (!client_read(client)) {
			client_delete(client);
			return true;
		}
	}
	if (server->can_write(server, client->_fd)) {
		client_write(client);
	}
	return client_handle(server, client, NULL);
}

static bool	check_tcp_player(player_t *player, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);

	if (server->can_read(server, player->client->_fd)) {
		if (!client_read(player->client)) {
			remove_client_from_list(server, player->client, true);
			DELETE(player);
			return true;
		}
	}
	if (server->can_write(server, player->client->_fd)) {
		client_write(player->client);
	}
	if (!player_is_busy(player)) {
		return client_handle(server, player->client, player);
	}
	return false;
}

static void	check_tcp_clients(t_server *server)
{
	list_it_fct_remove_t cfct = (list_it_fct_remove_t)check_tcp_client;
	list_it_fct_remove_t pfct = (list_it_fct_remove_t)check_tcp_player;

	list_it_remove(server->spectators_clients, cfct, server);
	list_it_remove(server->map->players, pfct, server);
	list_it_remove(server->anonymous_clients, cfct, server);
}

static void	handle_time(t_server *server)
{
	list_iterator_t	it;

	if (!INIT(LIST_IT, it, server->map->players))
		return;
	while (list_it_can_iterate(&it)) {
		player_wait(list_it_get(&it));
		list_it_iterate(&it);
	}
	DEINIT(it);
}

int	test_tcp_connection(int ac, char **av)
{
	map_t		*map = NEW(MAP, 10, 10);
	t_server	*server = init_struct_server(map);

	if (!server || ac != 2 || !map)
		return (84);
	setup_signals(server);
	int	port = atoi(av[1]);
	//* tmp
	add_team(server, "red", 12);
	add_team(server, "blue", 12);
	if (server->init(server, port, "TCP") == -1)
		return (84);
	while (1) {
		server->select(server, TIMEOUT);
		check_tcp_clients(server);
		if (server->can_read(server, server->_fd_server)) {
			server->add_client(server);
		}
		handle_time(server);
		//todo clock f
		DEBUG("..");
		sleep(1);
	}
	deinit_server(server);
	return (0);
}
