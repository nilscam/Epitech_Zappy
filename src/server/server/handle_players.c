/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_players.c
*/

#include "server.h"
#include "player.h"

void	handle_players_action(t_server *server)
{
	list_iterator_t	it;

	if (!INIT(LIST_IT, it, server->map->players))
		return;
	while (list_it_can_iterate(&it)) {
		player_wait(list_it_get(&it));
		list_it_iterate(&it);
	}
	DEINIT(it);
}

bool	can_simulate_game(t_server *server)
{
	zclock_t	*zclock = &server->zclock;
	double		us_to_wait = 1.0 / server->f * 1E6;

	if (zclock_time_since_mark(zclock, MICROSECONDS) >= us_to_wait) {
		zclock_mark(zclock);
		return true;
	}
	return false;
}
