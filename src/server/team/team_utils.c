/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** team_utils.c
*/

#include "team.h"

bool	team_can_add_player(team_t *team)
{
	return team->nb_players < team->max_players;
}

bool	team_add_player(team_t *team)
{
	if (team_can_add_player(team)) {
		++team->nb_players;
		return true;
	}
	return false;
}

void	team_remove_player(team_t *team)
{
	if (team->nb_players > 0) {
		--team->nb_players;
	}
}

size_t	team_available_players(team_t *team)
{
	return team->max_players - team->nb_players;
}