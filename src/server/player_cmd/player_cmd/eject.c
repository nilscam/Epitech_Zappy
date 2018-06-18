/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** eject.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"
#include "map_it.h"

static void	count_players(
	__attribute__((unused))player_t *player, va_list *args)
{
	int	*nb_players = va_arg(*args, int *);

	++(*nb_players);
}

static void	eject_players(player_t *player, va_list *args)
{
	int		player_id = va_arg(*args, int);
	direction_t	dir = va_arg(*args, direction_t);

	if (player->id == player_id)
		return;
	player_move_toward(player, dir, 1);
	dir = direction_turn_left(direction_turn_left(dir));
	client_callback(CB_EJECT, player->client, direction_to_int(dir));
}

bool	validate_eject(player_cmd_arg_t *args)
{
	int	nb_players = 0;

	map_it_players_at(args->server->map, args->player->pos->pos,
		(map_it_pl_t)count_players, &nb_players);
	if (nb_players <= 1) {
		client_callback(CB_KO, args->client);
		return false;
	}
	return true;
}

void	player_cmd_eject(player_cmd_arg_t *args)
{
	map_it_players_at(args->server->map,
		args->player->pos->pos,
		(map_it_pl_t)eject_players,
		args->player->id, args->player->dir);
	client_callback(CB_OK, args->client);
}
