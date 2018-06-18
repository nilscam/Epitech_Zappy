/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** elevation.c
*/

#include "map_it.h"

static void	count_players(player_t *player, va_list *args)
{
	int	*nb_players = va_arg(*args, int *);
	int	level = va_arg(*args, int);

	if (player->level == level) {
		++(*nb_players);
	}
}

bool	player_can_elevate(map_t *self, player_t *player)
{
	int	*stones = (int *)player->pos->inventory.stones;
	int	level = player->level;
	int	nb_players = 0;

	map_it_players_at(self, player->pos->pos,
		(map_it_pl_t)count_players, &nb_players, level);
	return elevation_can_elevate(level, nb_players, stones);
}
