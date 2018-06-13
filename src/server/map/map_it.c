/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_it.c
*/

#include "map_it.h"

static void	call_fct(map_it_pl_t fct, player_t *pl, va_list *args)
{
	va_list	cp_args;

	if (fct) {
		va_copy(cp_args, *args);
		fct(pl, &cp_args);
		va_end(cp_args);
	}
}

bool	map_it_players(map_t *self, map_it_pl_t fct, ...)
{
	list_iterator_t *it = NEW(LIST_IT, self->players);
	va_list		args;
	bool		has_it = false;

	va_start(args, fct);
	while (it && list_it_can_iterate(it)) {
		has_it = true;
		call_fct(fct, list_it_get(it), &args);
		list_it_iterate(it);
	}
	va_end(args);
	SAFE_DELETE(it);
	return has_it;
}

bool	map_it_players_at(map_t *self, point_t pos, map_it_pl_t fct, ...)
{
	list_iterator_t *it = NEW(LIST_IT, self->players);
	player_t	*player;
	va_list		args;
	bool		has_it = false;

	va_start(args, fct);
	while (it && list_it_can_iterate(it)) {
		player = list_it_get(it);
		if (point_are_equals(player->pos->pos, pos)) {
			has_it = true;
			call_fct(fct, player, &args);
		}
		list_it_iterate(it);
	}
	va_end(args);
	SAFE_DELETE(it);
	return has_it;
}

bool	map_it_players_team(map_t *self, const char *team,
		map_it_pl_t fct, ...)
{
	list_iterator_t *it = NEW(LIST_IT, self->players);
	player_t	*player;
	va_list		args;
	bool		has_it = false;

	va_start(args, fct);
	while (it && list_it_can_iterate(it)) {
		player = list_it_get(it);
		if (strcmp(player->team, team) == 0) {
			has_it = true;
			call_fct(fct, list_it_get(it), &args);
		}
		list_it_iterate(it);
	}
	va_end(args);
	SAFE_DELETE(it);
	return has_it;
}
