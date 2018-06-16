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
