/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** point.h
*/

#ifndef point_HPP
#define point_HPP

#include "direction.h"

typedef struct
{
	int	x;
	int	y;
}	point_t;

point_t	point_move(point_t from, direction_t to, int inc);
void	point_print(point_t point);

#endif // !point_HPP
