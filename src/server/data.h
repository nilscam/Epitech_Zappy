/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** data.h
*/

#ifndef data_HPP
#define data_HPP

#include "map.h"
#include "point.h"

typedef enum inv_type_e		inv_type_t;
typedef struct inventory_s	inventory_t;
typedef struct case_s		case_t;
typedef struct point_s		point_t;
typedef struct list_node_s	list_node_t;
typedef struct list_s		list_t;

struct player_s
{
	case_t		*pos;
	inventory_t	inventory;
};

#endif // !data_HPP
