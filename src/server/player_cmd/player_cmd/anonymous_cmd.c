/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** anonymous_cmd.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "map_it.h"
#include "egg.h"

static void	add_player_from_ano(t_server *server, player_t *player)
{
	team_t		*team = player->team;

	client_callback(CB_WELCOME_PLAYER, player->client,
		team_available_players(team),
		server->map->size.x,
		server->map->size.y);
	player->client->type = CLIENT_PLAYER;
	list_push_back(server->players_clients, player->client);
	clients_callback(CB_NEW_PLAYER, server->spectators_clients,
		player->id,
		player->pos->pos.x,
		player->pos->pos.y,
		direction_to_int_spec(player->dir),
		player->level,
		team->name);
}

static void	add_player_from_egg(t_server *server,
	player_t *player, int egg_id)
{
	team_t		*team = player->team;

	client_callback(CB_WELCOME_PLAYER, player->client,
		team_available_players(team),
		server->map->size.x,
		server->map->size.y);
	player->client->type = CLIENT_PLAYER;
	list_push_back(server->players_clients, player->client);
	clients_callback(CB_PLAYER_CONNECTION_EGG,
		server->spectators_clients,
		egg_id, player->id,
		player->pos->pos.x,
		player->pos->pos.y,
		direction_to_int_spec(player->dir),
		player->level,
		team->name);
}

static player_t	*try_add_player_from_egg(t_server *server,
	client_t *client, team_t *team)
{
	list_iterator_t	it;
	egg_t		*egg;
	player_t	*player = NULL;

	if (!INIT(LIST_IT, it, server->map->eggs))
		return NULL;
	while (list_it_can_iterate(&it)) {
		egg = list_it_get(&it);
		if (egg_is_hatched(egg)
			&& strcmp(egg->team->name, team->name) == 0) {
			player = add_player_to_map_at(server->map,
				egg->pos->pos, team, client);
			add_player_from_egg(server, player, egg->id);
			list_it_erase(&it, delete_class);
			break;
		}
		list_it_iterate(&it);
	}
	DEINIT(it);
	return player;
}

static void	kill_anonymous(player_cmd_arg_t *a)
{
	client_callback(CB_FULL_TEAM, a->client);
	a->client->kill_me = true;
}

void	anonymous_cmd_anonymous(player_cmd_arg_t *a)
{
	team_t		*team = team_find(a->server->teams, a->cmd);
	player_t	*player;

	if (!team) {
		client_callback(CB_INVALID_TEAM_NAME, a->client);
		return;
	}
	player = try_add_player_from_egg(a->server, a->client, team);
	if (!player && team_can_add_player(team)) {
		team_add_player(team);
		player = add_player_to_map(a->server->map, team, a->client);
		if (player) {
			add_player_from_ano(a->server, player);
		} else {
			team_remove_player(team);
			kill_anonymous(a);
		}
	} else {
		kill_anonymous(a);
	}
}
