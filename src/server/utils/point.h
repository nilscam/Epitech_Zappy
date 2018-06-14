/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** point.h
*/

#ifndef point_HPP
#define point_HPP

#include "direction.h"
#include <stdbool.h>

typedef struct
{
	int	x;
	int	y;
}	point_t;

/* point.c */
point_t	point_move(point_t from, direction_t to, int inc);
void	point_print(point_t point);
bool	point_are_equals(point_t a, point_t b);
point_t	point_add(point_t a, point_t b);

#endif // !point_HPP
