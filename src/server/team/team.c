/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** team.c
*/

#include "team.h"
#include "class.h"
#include <stdlib.h>

team_t	*team_new(char *name, size_t max_players)
{
	team_t	*team = malloc(sizeof(team_t));

	if (team && name) {
		team->name = name;
		team->max_players = max_players;
		team->nb_players = max_players;
	}
	return team;
}

void	team_delete(team_t *team)
{
	if (team) {
		SAFE_FREE(team->name);
		SAFE_FREE(team);
	}
}

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
