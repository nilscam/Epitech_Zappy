/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player.h
*/

#ifndef player_HPP
#define player_HPP

#include "c_modular.h"
#include "map.h"

typedef struct
{
	class_t		__base__;
	map_t		*map;
	map_content_t	*pos;
	inventory_t	inventory;
	char		*team;
	char		*name;
	direction_t	dir;
}	player_t;

/* player_utils.c */
void	player_print(player_t *self);

/* player_move.c */
void	player_move(player_t *self);
void	player_move_to(player_t *self, point_t pos);
void	player_move_toward(player_t *self, direction_t dir, int inc);

/* player_turn.c */
void	player_turn_left(player_t *self);
void	player_turn_right(player_t *self);

/* player.c */
extern const class_t *PLAYER;

#endif // !player_HPP
