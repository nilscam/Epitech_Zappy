/*
** EPITECH PROJECT, 2018
** zappy
** File description:
** vision by Makrah
*/

#include <string.h>
#include <utils/point.h>
#include <player/player.h>
#include "map_it.h"
#include "map.h"

/* 	vision is lvl * 2 + 1		*/

char	*print_food(map_content_t *content, char *tmp, bool *space)
{
	if (content->inventory.food == 0)
		return (tmp);
	if (*space)
		tmp += sprintf(tmp, " ");
	else
		*space = true;
	for (int i = 0 ; i < content->inventory.food ; ++i)
		tmp += sprintf(tmp, "Food");
	return (tmp);
}

char	*print_stones(map_content_t *content, char *tmp, int vis_len, bool *space)
{
	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
		for (size_t t = 0 ; t < content->inventory.stones[i] ; ++t) {
			if (*space || vis_len == 0)
				tmp += sprintf(tmp, " ");
			else
				*space = true;
			i == LINEMATE ? tmp += sprintf(tmp, "Linemate") : 0;
			i == DERAUMERE ? tmp += sprintf(tmp, "Deraumere") : 0;
			i == SIBUR ? tmp += sprintf(tmp, "Sibur") : 0;
			i == MENDIANE ? tmp += sprintf(tmp, "Mendiane") : 0;
			i == PHIRAS ? tmp += sprintf(tmp, "Phiras") : 0;
			i == THYSTAME ? tmp += sprintf(tmp, "Thystame") : 0;
		}
	}
	return (tmp);
}


static void	tmp_add_player(player_t *player, va_list *args)
{
	char ** tmp = va_arg(*args, char **);
	bool *space = va_arg(*args, bool*);

	if (*space)
		*tmp += sprintf(*tmp, " ");
	else
		*space = true;
	*tmp += sprintf(*tmp, "%s", player->name);
}


char	*look_left(map_t *this, player_t *player)
{
	char vision[10000];
	char *tmp = vision;
	map_content_t *content;
	bool space = false;

	bzero(vision, 10000);
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 - vis_len ; vis_widt <= vis_len; ++vis_widt) {
			tmp += sprintf(tmp, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x + vis_widt, player->pos->pos.y + vis_len};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &tmp, &space);
			tmp = print_food(content, tmp, &space);
			tmp = print_stones(content, tmp, vis_len, &space);
			space = false;
		}
	}
	return (strdup((const char *)vision));
}

char	*look_right(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
{
	char vision[10000];
	char *tmp = vision;
	map_content_t *content;
	bool space = false;

	bzero(vision, 10000);
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 - vis_len ; vis_widt <= vis_len; ++vis_widt) {
			tmp += sprintf(tmp, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x + vis_widt, player->pos->pos.y + vis_len};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &tmp, &space);
			tmp = print_food(content, tmp, &space);
			tmp = print_stones(content, tmp, vis_len, &space);
			space = false;
		}
	}
	return (strdup((const char *)vision));
}

char	*look_up(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
{
	return (NULL);
}

char	*look_down(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
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
	return (NULL);
}