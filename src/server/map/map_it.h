/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_it.h
*/

#ifndef map_it_HPP
#define map_it_HPP

#include "map.h"
#include "player.h"

typedef void	(*map_it_pl_t)(player_t *, va_list *);

/* map_it.c */
bool	map_it_players(map_t *self, map_it_pl_t fct, ...);
bool	map_it_players_at(map_t *self, point_t pos, map_it_pl_t fct, ...);
bool	map_it_players_team(map_t *self, const char *team,
		map_it_pl_t fct, ...);

#endif // !map_it_HPP