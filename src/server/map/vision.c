/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** vision by Makrah
*/

#include <string.h>
#include <utils/point.h>
#include <player/player.h>
#include <big_buff/big_buff.h>
#include "map_it.h"
#include "map.h"
#include "big_buff.h"

/* 	vision is lvl * 2 + 1		*/

void	print_food(map_content_t *content, big_buff_t *buff)
{
	if (content->inventory.food == 0)
		return;
	for (int i = 0 ; i < content->inventory.food ; ++i)
		bb_add(buff, " food");
}

void	print_stones(map_content_t *content, big_buff_t *buff,
	__attribute__((unused))int vis_len)
{
	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
		for (size_t t = 0 ; t < content->inventory.stones[i] ; ++t) {
			i == LINEMATE ? bb_add(buff, " linemate") : 0;
			i == DERAUMERE ? bb_add(buff, " deraumere") : 0;
			i == SIBUR ? bb_add(buff, " sibur") : 0;
			i == MENDIANE ? bb_add(buff, " mendiane") : 0;
			i == PHIRAS ? bb_add(buff, " phiras") : 0;
			i == THYSTAME ? bb_add(buff, " thystame") : 0;
		}
	}
}

char	*look(map_t *this, player_t *player)
{
	switch (player->dir) {
	case DIR_LEFT:
		return (look_left(this, player));
	case DIR_RIGHT:
		return (look_right(this, player));
	case DIR_UP:
		return (look_up(this, player));
	case DIR_DOWN:
		return (look_down(this, player));
	default:
		return NULL;
	}
	return (NULL);
}