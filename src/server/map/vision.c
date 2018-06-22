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

/* 	vision is lvl * 2 + 1		*/

void	print_food(map_content_t *content, big_buff_t *buff)
{
	if (content->inventory.food == 0)
		return;
	for (int i = 0 ; i < content->inventory.food ; ++i)
		big_buff_add_format(buff, " food");
}

void	print_stones(map_content_t *content, big_buff_t *buff, __attribute__((unused))int vis_len)
{
	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
		for (size_t t = 0 ; t < content->inventory.stones[i] ; ++t) {
			i == LINEMATE ? big_buff_add_format(buff, " linemate") : 0;
			i == DERAUMERE ? big_buff_add_format(buff, " deraumere") : 0;
			i == SIBUR ? big_buff_add_format(buff, " sibur") : 0;
			i == MENDIANE ? big_buff_add_format(buff, " mendiane") : 0;
			i == PHIRAS ? big_buff_add_format(buff, " phiras") : 0;
			i == THYSTAME ? big_buff_add_format(buff, " thystame") : 0;
		}
	}
}


static void	tmp_add_player(player_t *player, va_list *args)
{
	big_buff_t *buff = va_arg(*args, big_buff_t *);

	big_buff_add_format(buff, " %s", player->name);
}

#include "big_buff.h"
char	*look_left(map_t *this, player_t *player)
{
	big_buff_t buff;
	map_content_t *content;

	big_buff_init(&buff);
	big_buff_add_format(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 + vis_len ; vis_widt >= -vis_len; --vis_widt) {
			big_buff_add_format(&buff, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x - vis_len, player->pos->pos.y + vis_widt};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	big_buff_add_format(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_right(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
{
	big_buff_t buff;
	map_content_t *content;

	big_buff_init(&buff);
	big_buff_add_format(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 - vis_len ; vis_widt <= vis_len; ++vis_widt) {
			big_buff_add_format(&buff, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x + vis_len, player->pos->pos.y + vis_widt};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	big_buff_add_format(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_down(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
{
	big_buff_t buff;
	map_content_t *content;

	big_buff_init(&buff);
	big_buff_add_format(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 + vis_len ; vis_widt >= -vis_len; --vis_widt) {
			big_buff_add_format(&buff, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x + vis_widt, player->pos->pos.y + vis_len};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	big_buff_add_format(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_up(__attribute__((unused))map_t *this, __attribute__((unused))player_t *player)
{
	big_buff_t buff;
	map_content_t *content;

	big_buff_init(&buff);
	big_buff_add_format(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int vis_widt = 0 - vis_len ; vis_widt <= vis_len; ++vis_widt) {
			big_buff_add_format(&buff, vis_len == 0 ? "" : ",");
			point_t pos = {player->pos->pos.x + vis_widt, player->pos->pos.y - vis_len};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	big_buff_add_format(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look(map_t *this, player_t *player)
{
/*	char vision[1000000];
	char *tmp = vision;
	map_content_t *content;
	bool space = false;

	bzero(vision, 1000000);
	for (int y = 0 ; y < this->size.y ; ++y) {
		for (int x = 0  ; x < this->size.x ; ++x) {
			tmp += sprintf(tmp, x == 0 ? "" : "\t|\t");
			point_t pos = {x, y};
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &tmp, &space);
			tmp = print_food(content, tmp, &space);
			tmp = print_stones(content, tmp, y, &space);
			space = false;
		}
		printf("line %d\n%s\n", y, vision);
		bzero(vision, 1000000);
		tmp = vision;
	}*/
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