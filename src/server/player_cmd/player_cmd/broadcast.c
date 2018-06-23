/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** broadcast.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

static int	convert_dir_to_int(
	direction_t from_dir, direction_t player_dir)
{
	if (from_dir == DIR_NONE)
		return 0;
	if (player_dir & DIR_RIGHT)
		from_dir = direction_turn_right(from_dir);
	if (player_dir & DIR_LEFT)
		from_dir = direction_turn_left(from_dir);
	if (player_dir & DIR_DOWN)
		from_dir = direction_turn_left(
			direction_turn_left(from_dir));
	return direction_to_int(from_dir);
}

static void	broadcast_to_player(player_t *player, va_list *args)
{
	map_t	*map = va_arg(*args, map_t *);
	point_t	*from = va_arg(*args, point_t *);
	int	from_id = va_arg(*args, int);
	char	*msg = va_arg(*args, char *);
	direction_t	dir;

	if (from_id == player->id)
		return;
	dir = map_dir_sound_from(map, *from, player->pos->pos);
	client_callback(CB_BROADCAST, player->client,
		convert_dir_to_int(dir, player->dir), msg);
}

void	player_cmd_broadcast(player_cmd_arg_t *args)
{
	map_t	*map = args->server->map;
	point_t	from = args->player->pos->pos;
	char	*msg;

	if (args->nb_args > 1) {
		msg = args->cmd + strlen(args->c->cmd) + 1;
		DEBUG("broadcast from fd %d: '%s'", args->client->fd, msg);
		list_it_all(map->players,
			(list_it_fct_t)broadcast_to_player,
			map, &from, args->player->id, msg);
		clients_callback(CB_BROADCAST,
			args->server->spectators_clients,
			args->player->id, msg);
	}
	client_callback(CB_OK, args->client);
}
