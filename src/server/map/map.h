/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.h
*/

#ifndef map_HPP
#define map_HPP

#include "class.h"
#include "point.h"
#include "list.h"
#include "list_iterator.h"
#include "client.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum
{
	LINEMATE,
	DERAUMERE,
	SIBUR,
	MENDIANE,
	PHIRAS,
	THYSTAME,
	NUMBER_OF_INV_TYPE
}	inv_type_t;

typedef struct
{
	inv_type_t	stones[NUMBER_OF_INV_TYPE];
	int		food;
}	inventory_t;

typedef struct
{
	point_t		pos;
	inventory_t	inventory;
}	map_content_t;

typedef struct
{
	class_t		__base__;
	point_t		size;
	map_content_t	*cases_buff;
	map_content_t	**cases;
	list_t		*players;
}	map_t;

/* map_init.c */
void	init_map_contents(map_t *self);

/* map_move.c */
bool	map_is_in_map(map_t *self, point_t pos);
point_t	map_move(map_t *self, point_t from, direction_t to, int inc);

/* map_utils.c */
map_content_t	*map_content_at(map_t *self, point_t pos);
bool	add_player_to_map_at(map_t *map, point_t pos,
		const char *team, client_t *client);
bool	add_player_to_map(map_t *map, client_t *client);

//todo CLIENT-NUM ---> list_t *teams

/* map_sound.c */
direction_t	map_dir_sound_from(map_t *self, point_t from, point_t to);

/* inventory.c */
void	init_map_inventory(inventory_t *inv);
void	init_player_inventory(inventory_t *inv);

/* map.c */
extern const class_t *MAP;

#endif // !map_HPP
