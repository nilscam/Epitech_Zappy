/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** name_teams.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_name_teams(player_cmd_arg_t *args)
{
	list_iterator_t	it;
	team_t		*team;

	if (!INIT(LIST_IT, it, args->server->teams))
		return;
	while (list_it_can_iterate(&it)) {
		team = list_it_get(&it);
		client_callback(CB_NAME_TEAMS, args->client, team->name);
		list_it_iterate(&it);
	}
	DEINIT(it);
}
