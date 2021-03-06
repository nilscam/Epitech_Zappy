/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_eggs.c
*/

#include "server.h"
#include "egg.h"
#include "player_callback.h"

void	handle_eggs_action(t_server *server)
{
	list_iterator_t	it;
	egg_t		*egg;

	if (!INIT(LIST_IT, it, server->map->eggs))
		return;
	while (list_it_can_iterate(&it)) {
		egg = list_it_get(&it);
		egg_wait(egg);
		if (egg_will_hatch(egg)) {
			clients_callback(CB_EGG_HATCHING,
				server->spectators_clients, egg->id);
		} else {
			list_it_iterate(&it);
		}
	}
	DEINIT(it);
}
