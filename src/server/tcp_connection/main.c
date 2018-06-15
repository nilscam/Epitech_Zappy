/*
** EPITECH PROJECT, 2018
** main_test
** File description:
** main
*/

#include "tcp_connection.h"
#include "player.h"
#include "save_signal.h"

int		read_data(t_server *server, player_t *player)
{
	char	buff[SIZE_BUFF];

	(void)server;
	int ret = read(player->client->_fd, buff, SIZE_BUFF - 1);
	if  (ret <= 0) {
		return (0);
	}
	buff[ret] = 0;
	buff_put(&player->client->_cbuf, buff);
	if (buff[ret - 1] == '\n') {
		char *str = buff_get(&player->client->_cbuf);
		printf("[%s]\n", str);
	}
	return (1);
}

static void	check_tcp_clients(t_server *server)
{
	list_iterator_t it;
	player_t	*player;

	if (!INIT(LIST_IT, it, server->players))
		return;
	while (list_it_can_iterate(&it)) {
		player = list_it_get(&it);
		if (server->can_read(server, player->client->_fd)) {
			DEBUG("can_read from %d", player->client->_fd);
			if (!read_data(server, player)) {
				DEBUG("remove client from %d", player->client->_fd);
				list_it_erase(&it, (void (*)(void *))delete_class);
				continue;
			}
		}
		if (player && server->can_write(server, player->client->_fd)) {}
		if (player && server->can_err(server, player->client->_fd)) {}
		list_it_iterate(&it);
	}
	DEINIT(it);
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
		server->select(server, map, TIMEOUT);
		check_tcp_clients(server);
		if (server->can_read(server, server->_fd_server)) {
			server->add_client(server, map);
		}
	}
	deinit_server(server);
	return (0);
}