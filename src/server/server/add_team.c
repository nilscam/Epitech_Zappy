/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** add_team.c
*/

#include "server.h"

void	add_team(t_server *this, const char *name, size_t max_players)
{
	team_t	*team = team_new(strdup(name), max_players);

	if (team) {
		list_push_back(this->teams, team);
	}
}
