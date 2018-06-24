/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_it.h
*/

#ifndef map_it_HPP
#define map_it_HPP

#include "map.h"
#include "player.h"
#include "big_buff.h"

typedef void	(*map_it_pl_t)(player_t *, va_list *);

// /* map_it.c */
bool	map_it_players_at(map_t *self, point_t pos, map_it_pl_t fct, ...);
player_t	*get_player_from_id(map_t *self, int id);

/* map_utils.c */
player_t	*add_player_to_map(map_t *map,
	const team_t *team, client_t *client);
player_t	*add_player_to_map_at(map_t *map, point_t pos,
	const team_t *team, client_t *client);

/* vision.c */
void	print_stones(map_content_t *content, big_buff_t *buff, int vis_len);
void	print_food(map_content_t *content, big_buff_t *buff);
char	*look(map_t *this, player_t *player);

/* vision_dir.c */
char	*look_left(map_t *this, player_t *player);
char	*look_right(map_t *this, player_t *player);
char	*look_down(map_t *this, player_t *player);
char	*look_up(map_t *this, player_t *player);

/* elevation.c */
bool	player_can_elevate(map_t *self, player_t *player);

/* stat.c */
void	remove_inv_from_to(inventory_t *from, inventory_t *to);
void	count_inv_in_map(map_t *self, inventory_t *inv);

#endif // !map_it_HPP
