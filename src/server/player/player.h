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
	int		level;
}	player_t;

struct elevation_tab_s
{
	int		level;
	int		nb_players;
	int		stones[NUMBER_OF_INV_TYPE];
};

/* player_elevation.c */
bool	elevation_can_elevate(int level, int nb_of_players, int *stones);
void	player_elevate(player_t *self);

/* player_move.c */
void	player_move(player_t *self);
void	player_move_to(player_t *self, point_t pos);
void	player_move_toward(player_t *self, direction_t dir, int inc);

/* player_turn.c */
void	player_turn_left(player_t *self);
void	player_turn_right(player_t *self);

/* player_utils.c */
void	player_print(player_t *self);

/* player.c */
extern const class_t *PLAYER;

#endif // !player_HPP
