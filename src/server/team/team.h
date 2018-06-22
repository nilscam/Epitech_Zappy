/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** team.h
*/

#ifndef team_HPP
#define team_HPP

#include "list.h"
#include <stddef.h>
#include <stdbool.h>

typedef struct
{
	char	*name;
	size_t	max_players;
	size_t	nb_players;
}	team_t;

/* team.c */
team_t	*team_new(char *name, size_t max_players);
void	team_delete(team_t *team);

/* team_utils.c */
void	team_add_max_player(team_t *team);
bool	team_can_add_player(team_t *team);
bool	team_add_player(team_t *team);
void	team_remove_player(team_t *team);
size_t	team_available_players(team_t *team);

/* team_find.c */
team_t	*team_find(list_t *teams, char *name);

#endif // !team_HPP
