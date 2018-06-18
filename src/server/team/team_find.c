/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** team_find.c
*/

#include "team.h"
#include "list_iterator.h"

static bool	is_team(team_t *team, va_list *args)
{
	const char	*name = va_arg(*args, const char *);

	return strcmp(name, team->name) == 0;
}

team_t	*team_find(list_t *teams, char *name)
{
	return list_it_find(teams, (list_it_fct_find_t)is_team, name);
}
