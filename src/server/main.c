/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.c
*/

#include "server.h"
#include "parsing.h"
#include "save_signal.h"
#include <errno.h>

int	test(int ac, char **av);

static map_t	*infos_init_map(t_infos *infos)
{
	srand((unsigned int)time(NULL));
	return NEW(MAP, infos->_width, infos->_height);
}

static t_server	*infos_init_server(map_t *map, t_infos *infos)
{
	t_server *server = init_struct_server(map, infos->_freq);

	if (!server || server->init(server, infos->_port, "TCP") < 0)
		return NULL;
	setup_signals(server);
	for (int i = -1; infos->_team_name && infos->_team_name[++i];) {
		add_team(server, infos->_team_name[i], infos->_max_per_team);
		free(infos->_team_name[i]);
	}
	SAFE_FREE(infos->_team_name);
	return server;
}

static int	start_server_loop(t_server *server)
{
	while (true) {
		server->select(server, TIMEOUT);
		handle_tcp_clients(server);
		handle_tcp_server(server);
		if (can_simulate_game(server)) {
			handle_players_action(server);
		}
	}
	return 0;
}

int	main(int ac, char **av)
{
	t_infos		infos = parse_args(ac, av);
	t_server	*server;

	if (!infos._err) {
		dprintf(2, "Parsing error\n");
		return (84);
	}
	server = infos_init_server(infos_init_map(&infos), &infos);
	if (!server) {
		dprintf(2, "Error: %s\n", strerror(errno));
		return (84);
	}
	start_server_loop(server);
	deinit_server(server);
	return 0;
}
