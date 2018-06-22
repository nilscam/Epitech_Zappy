/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_players.c
*/

#include "server.h"
#include "player.h"
#include "player_callback.h"

void	handle_players_action(t_server *server)
{
	list_iterator_t	it;
	player_t	*player;

	if (!INIT(LIST_IT, it, server->map->players))
		return;
	while (list_it_can_iterate(&it)) {
		player = list_it_get(&it);
		player_consume_time(player);
		if (!player->is_waiting_to_die
			&& player_is_dead_of_hunger(player)) {
			client_callback(CB_DEATH_PLAYER, player->client);
			player->client->kill_me = true;
			player->is_waiting_to_die = true;
		} else {
			player_wait(player);
		}
		list_it_iterate(&it);
	}
	DEINIT(it);
}

bool	can_simulate_game(t_server *server)
{
	zclock_t	*zclock = &server->zclock;
	bool		can_wait = server->f > 0;
	double		us_to_wait;

	if (!can_wait)
		return false;
	us_to_wait = 1.0 / server->f * 1E6;
	if (zclock_time_since_mark(zclock, MICROSECONDS) >= us_to_wait) {
		zclock_mark(zclock);
		return true;
	}
	return false;
}
