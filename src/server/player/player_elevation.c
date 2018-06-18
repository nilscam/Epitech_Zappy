/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_elevation.c
*/

#include "player.h"

static const struct elevation_tab_s	ELEVATIONS[] = {
	{ 1, 1, { 1, 0, 0, 0, 0, 0 } },
	{ 2, 2, { 1, 1, 1, 0, 0, 0 } },
	{ 3, 2, { 2, 0, 1, 0, 2, 0 } },
	{ 4, 4, { 1, 1, 2, 0, 1, 0 } },
	{ 5, 4, { 1, 2, 1, 3, 0, 0 } },
	{ 6, 6, { 1, 2, 3, 0, 1, 0 } },
	{ 7, 6, { 2, 2, 2, 2, 2, 1 } }
};

bool	elevation_can_elevate(int level, int nb_of_players, int *stones)
{
	const struct elevation_tab_s	*el = NULL;
	int max_el = sizeof(ELEVATIONS) / sizeof(struct elevation_tab_s);

	for (int i = 0; i < max_el; ++i) {
		if (level == ELEVATIONS[i].level) {
			el = &ELEVATIONS[i];
			break;
		}
	}
	if (!el)
		return false;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i)
		if (stones[i] != el->stones[i])
			return false;
	return nb_of_players == el->nb_players;
}

void	player_elevate(player_t *self)
{
	++self->level;
}
