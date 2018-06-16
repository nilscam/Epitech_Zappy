/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** anonymous_cmd.c
*/

#include "player_cmd.h"
#include "player_callback.h"

static bool	is_team(team_t *team, va_list *args)
{
	const char	*name = va_arg(*args, const char *);

	return strcmp(name, team->name) == 0;
}

void	anonymous_cmd_anonymous(player_cmd_arg_t *args)
{
	t_server	*server = args->server;
	client_t	*client = args->client;
	team_t		*team = list_it_find(server->teams,
		(list_it_fct_find_t)is_team, args->cmd);

	if (team && add_player_to_map(server->map, team, client)) {
		client_callback(CB_WELCOME_PLAYER, client,
			team_available_players(team),
			server->map->size.x,
			server->map->size.y);
		client->type = CLIENT_PLAYER;
		list_push_back(server->players_clients, client);
	} else {
		client_callback(CB_INVALID_TEAM_NAME, client);
	}
}

void	anonymous_cmd_spectator(player_cmd_arg_t *args)
{
	t_server	*server = args->server;
	client_t	*client = args->client;

	client_callback(CB_WELCOME_SPECTATOR, client);
	client->type = CLIENT_SPECTATOR;
	list_push_back(server->spectators_clients, client);
}
