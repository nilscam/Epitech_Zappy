/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.c
*/

#include "server.h"
#include "parsing.h"
#include "save_signal.h"
#include "player_callback.h"
#include <errno.h>

int	tests(int ac, char **av);

static map_t	*infos_init_map(t_infos *infos)
{
	int	nb_teams = 0;

	srand((unsigned int)time(NULL));
	while (infos->_team_name && infos->_team_name[++nb_teams]);
	return NEW(MAP, infos->_width, infos->_height, infos->_max_per_team, nb_teams);
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
	while (!server->winner) {
		server->select(server, TIMEOUT);
		handle_tcp_clients(server);
		handle_tcp_server(server);
		if (can_simulate_game(server)) {
			handle_players_action(server);
			handle_eggs_action(server);
		}
	}
	clients_callback(CB_END_OF_GAME, server->spectators_clients,
		server->winner->name);
	printf("winner: %s\n", server->winner->name);
	return 0;
}

int	main(int ac, char **av)
{
	srand((unsigned int)time(NULL));
	return tests(ac, av);
	t_infos		infos = parse_args(ac, av);
	t_server	*server;

	if (infos._is_help)
		return (help(av[0]));
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
