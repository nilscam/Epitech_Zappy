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

static void 	underway_validate(player_t *pl, va_list *args)
{
	int		*remaining_players = va_arg(*args, int *);
	int		level = va_arg(*args, int);
	int		id = va_arg(*args, int);
	bool		valid = va_arg(*args, int);

	if (pl->id == id || (*remaining_players > 1 && pl->level == level))
	{
		*remaining_players -= (pl->id != id);
		if (pl->id == id) {
			client_callback(valid ? CB_OK : CB_KO, pl->client);
		} else if (valid) {
			client_callback(CB_ELEVATION_UNDERWAY, pl->client);
		}
	}
}

static void 	underway_confirm(player_t *pl, va_list *args)
{
	t_server	*server = va_arg(*args, t_server *);
	int		*remaining_players = va_arg(*args, int *);
	int		level = va_arg(*args, int);
	int		id = va_arg(*args, int);
	bool		valid = va_arg(*args, int);

	if (pl->id == id || (*remaining_players > 1 && pl->level == level))
	{
		*remaining_players -= (pl->id != id);
		if (valid) {
			client_callback(CB_CURRENT_LVL, pl->client, ++pl->level);
			clients_callback(CB_PLAYER_LEVEL,
				server->spectators_clients, pl->id, pl->level);
		} else {
			client_callback(CB_ELEVATION_FAILED, pl->client);
		}
	}
}

bool	validate_incant(player_cmd_arg_t *args)
{
	elevation_tab_t	*tab = get_elevation_at_level(args->player->level);
	int		remaining_players = tab ? tab->nb_players : 0;
	bool		is_valid = false;

	if (player_can_elevate(args->server->map, args->player)) {
		is_valid = true;
		args->player->is_elevating = true;
		clients_callback(CB_START_INCANTATION,
			args->server->spectators_clients,
			args->player->pos->pos.x, args->player->pos->pos.y,
			args->player->level, args->player->id,
			args->server->map);
	}
	map_it_players_at(args->server->map, args->player->pos->pos,
		(map_it_pl_t)underway_validate,
		&remaining_players, args->player->level,
		args->player->id, is_valid);
	return is_valid;
}

void	player_cmd_incantation(player_cmd_arg_t *args)
{
	elevation_tab_t	*tab = get_elevation_at_level(args->player->level);
	int		remaining_players = tab ? tab->nb_players : 0;
	bool		is_valid = false;

	if (player_can_elevate(args->server->map, args->player)) {
		is_valid = true;
		args->player->is_elevating = false;
		consume_inventory_elevation(&args->player->pos->inventory,
			args->player->level);
	}
	map_it_players_at(args->server->map, args->player->pos->pos,
		(map_it_pl_t)underway_confirm, args->server,
		&remaining_players, args->player->level,
		args->player->id, is_valid);
	clients_callback(CB_END_INCANTATION,
		args->server->spectators_clients,
		args->player->pos->pos.x, args->player->pos->pos.y,
		is_valid ? "ok" : "ko");
}
