/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** fork.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "egg.h"

bool	validate_fork(player_cmd_arg_t *args)
{
	clients_callback(CB_EGG_LAYING, args->server->spectators_clients,
		args->player->id);
	return true;
}

void	player_cmd_fork(player_cmd_arg_t *args)
{
	map_t		*map = args->server->map;
	map_content_t	*pos = args->player->pos;
	team_t		*team = args->player->team;
	egg_t		*egg = NEW(EGG, map, pos, team);

	list_push_back(args->server->map->eggs, egg);
	client_callback(CB_OK, args->client);
	clients_callback(CB_EGG_LAID_BY_PLAYER,
		args->server->spectators_clients,
		egg->id,
		args->player->id,
		egg->pos->pos.x,
		egg->pos->pos.y);
}
