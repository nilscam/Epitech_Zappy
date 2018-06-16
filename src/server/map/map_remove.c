/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_remove.c
*/

#include "map.h"
#include "player.h"

void	map_remove_player_with_fd(map_t *self, int fd)
{
	list_iterator_t it;
	player_t	*player;

	if (!INIT(LIST_IT, it, self->players))
		return;
	while (list_it_can_iterate(&it)) {
		player = list_it_get(&it);
		if (fd == player->client->_fd) {
			list_it_erase(&it, delete_class);
		} else {
			list_it_iterate(&it);
		}
	}
	DEINIT(it);
}
