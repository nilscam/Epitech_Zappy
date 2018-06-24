/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** vision_dir.c
*/

#include <string.h>
#include <utils/point.h>
#include <player/player.h>
#include <big_buff/big_buff.h>
#include "map_it.h"
#include "map.h"

static void	tmp_add_player(player_t *player, va_list *args)
{
	big_buff_t *buff = va_arg(*args, big_buff_t *);

	bb_add(buff, " %s", player->name);
}

char	*look_left(map_t *this, player_t *player)
{
	big_buff_t	buff;
	map_content_t	*content;
	point_t		pos;

	big_buff_init(&buff);
	bb_add(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int w = 0 + vis_len ; w >= -vis_len; --w) {
			bb_add(&buff, vis_len == 0 ? "" : ",");
			pos.x = player->pos->pos.x - vis_len;
			pos.y = player->pos->pos.y + w;
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	bb_add(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_right(map_t *this, player_t *player)
{
	big_buff_t	buff;
	map_content_t	*content;
	point_t		pos;

	big_buff_init(&buff);
	bb_add(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int w = 0 - vis_len ; w <= vis_len; ++w) {
			bb_add(&buff, vis_len == 0 ? "" : ",");
			pos.x = player->pos->pos.x + vis_len;
			pos.y = player->pos->pos.y + w;
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	bb_add(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_down(map_t *this, player_t *player)
{
	big_buff_t	buff;
	map_content_t	*content;
	point_t		pos;

	big_buff_init(&buff);
	bb_add(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int w = 0 + vis_len ; w >= -vis_len; --w) {
			bb_add(&buff, vis_len == 0 ? "" : ",");
			pos.x = player->pos->pos.x + w;
			pos.y = player->pos->pos.y + vis_len;
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	bb_add(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}

char	*look_up(map_t *this, player_t *player)
{
	big_buff_t	buff;
	map_content_t	*content;
	point_t		pos;

	big_buff_init(&buff);
	bb_add(&buff, "[");
	for (int vis_len = 0 ; vis_len <= player->level ; ++vis_len) {
		for (int w = 0 - vis_len ; w <= vis_len; ++w) {
			bb_add(&buff, vis_len == 0 ? "" : ",");
			pos.x = player->pos->pos.x + w;
			pos.y = player->pos->pos.y - vis_len;
			content = map_content_at(this, pos);
			map_it_players_at(this, pos, tmp_add_player, &buff);
			print_food(content, &buff);
			print_stones(content, &buff, vis_len);
		}
	}
	bb_add(&buff, " ]\n");
	return (big_buff_cpy_data(&buff));
}
