/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.h
*/

#ifndef map_HPP
#define map_HPP

#include "c_modular.h"
#include "point.h"

#include <stdbool.h>

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
	// list_t		players;
}	map_t;

extern const class_t *MAP;

#endif // !map_HPP
