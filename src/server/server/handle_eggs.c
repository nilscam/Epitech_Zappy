/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** handle_eggs.c
*/

#include "server.h"
#include "egg.h"

void	handle_eggs_action(t_server *server)
{
	list_iterator_t	it;
	egg_t		*egg;

	if (!INIT(LIST_IT, it, server->map->players))
		return;
	while (list_it_can_iterate(&it)) {
		egg = list_it_get(&it);
		egg_wait(egg);
		if (egg_is_hatched(egg)) {
			team_add_max_player(egg->team);
			list_it_erase(&it, delete_class);
		} else {
			list_it_iterate(&it);
		}
	}
	DEINIT(it);
}
