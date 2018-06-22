/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** incantation.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "map_it.h"

static void	elevation_underway(player_t *pl, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);
	int		*remaining_players = va_arg(*args, int *);
	int		level = va_arg(*args, int);
	int		id = va_arg(*args, int);
	bool		is_validating = va_arg(*args, int);
	inventory_t	trash;

	if (pl->id == id || (*remaining_players > 1 && pl->level == level)) {
		if (is_validating) {
			--(*remaining_players);
			client_callback(CB_ELEVATION_UNDERWAY, pl->client);
			return;
		}
		remove_inv_from_to(&pl->pos->inventory, &trash);
		client_callback(CB_CURRENT_LVL, pl->client, ++pl->level);
		clients_callback(CB_PLAYER_LEVEL,
			server->spectators_clients, pl->id, pl->level);
	}
}

bool	validate_incant(player_cmd_arg_t *args)
{
	elevation_tab_t	*tab = get_elevation_at_level(args->player->level);
	int		remaining_players = tab ? tab->nb_players : 0;

	if (player_can_elevate(args->server->map, args->player)) {
		map_it_players_at(args->server->map, args->player->pos->pos,
			(map_it_pl_t)elevation_underway, args->server,
			&remaining_players, args->player->level,
			args->player->id, true);
		clients_callback(CB_START_INCANTATION,
			args->server->spectators_clients,
			args->player->pos->pos.x, args->player->pos->pos.y,
			args->player->level, args->player->id,
			args->server->map);
		args->player->is_elevating = true;
		return true;
	} else {
		client_callback(CB_KO, args->client);
		return false;
	}
}

void	player_cmd_incantation(player_cmd_arg_t *args)
{
	bool		success = false;
	elevation_tab_t	*tab = get_elevation_at_level(args->player->level);
	int		remaining_players = tab ? tab->nb_players : 0;

	args->player->is_elevating = false;
	if (player_can_elevate(args->server->map, args->player)) {
		success = true;
		map_it_players_at(args->server->map, args->player->pos->pos,
			(map_it_pl_t)elevation_underway, args->server,
			&remaining_players, args->player->level,
			args->player->id, false);
	} else {
		client_callback(CB_KO, args->client);
	}
	clients_callback(CB_END_INCANTATION,
		args->server->spectators_clients,
		args->player->pos->pos.x, args->player->pos->pos.y,
		success ? "ok" : "ko");
}
