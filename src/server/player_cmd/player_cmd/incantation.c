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

bool	validate_incant(player_cmd_arg_t *args)
{
	if (player_can_elevate(args->server->map, args->player)) {
		client_callback(CB_ELEVATION_UNDERWAY, args->client);
		clients_callback(CB_START_INCANTATION,
			args->server->spectators_clients,
			args->player->pos->pos.x,
			args->player->pos->pos.y,
			args->player->level,
			args->player->id,
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
	bool	success = false;

	args->player->is_elevating = false;
	if (player_can_elevate(args->server->map, args->player)) {
		success = true;
		empty_stones_inventory(&args->player->pos->inventory);
		client_callback(CB_CURRENT_LVL, args->client,
			++args->player->level);
		clients_callback(CB_PLAYER_LEVEL,
			args->server->spectators_clients,
			args->player->id, args->player->level);
	} else {
		client_callback(CB_KO, args->client);
	}
	clients_callback(CB_END_INCANTATION,
		args->server->spectators_clients,
		args->player->pos->pos.x, args->player->pos->pos.y,
		success ? "ok" : "ko");
}
