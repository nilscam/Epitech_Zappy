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
#include "zclock.h"

int	test_tcp_connection(int ac, char **av)
{
	map_t		*map = NEW(MAP, 10, 10);
	t_server	*server = init_struct_server(map, 1.0);
	zclock_t	zclock;

	if (!server || ac != 2 || !map || !INIT(ZCLOCK, zclock))
		return (84);
	setup_signals(server);
	int	port = atoi(av[1]);
	add_team(server, "red", 12);
	add_team(server, "blue", 12);
	if (server->init(server, port, "TCP") == -1)
		return (84);
	while (1) {
		server->select(server, TIMEOUT);
		handle_tcp_clients(server);
		handle_tcp_server(server);
		if (can_simulate_game(server)) {
			handle_players_action(server);
		}
	}
	deinit_server(server);
	return (0);
}
