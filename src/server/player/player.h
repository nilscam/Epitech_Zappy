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
}	player_t;

/* player_utils.c */
void	player_print(player_t *self);

/* player.c */
extern const class_t *PLAYER;

#endif // !player_HPP
