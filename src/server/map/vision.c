/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** vision by Makrah
*/

#include "map.h"

/* 	vision is lvl * 2 + 1		*/

char	*look_left(map_t *this, player_t *player)
{
	int x = player->pos->pos.x;
	int y = player->pos->pos.y;
	char *vision[2000];

	bzero(vision, 2000);
	for (size_t vis_len = 1 ; vis_len < player->level ; ++vis_len) {
		for (int vis_widt = 0 - player->level ; vis_widt < player->level ; ++vis_widt) {
			for (int stone = 0 ; stone < NUMBER_OF_INV_TYPE ; ++stone)
			sprintf((char *)vision, "%d ", (this->cases[vis_len][vis_widt].inventory.stones[stone]));
			sprintf((char *)vision, ",");
		}
	}
	printf("%s\n", (char *)vision);
}

char	*look_right(map_t *this, player_t *player)
{
	return (NULL);
}

char	*look_up(map_t *this, player_t *player)
{
	return (NULL);
}

char	*look_down(map_t *this, player_t *player)
{
	return (NULL);
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
}