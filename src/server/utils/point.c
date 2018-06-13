/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** point.c
*/

#include "point.h"
#include <stdio.h>

point_t	point_move(point_t from, direction_t to, int inc)
{
	from.x += (to & DIR_LEFT ? -inc : 0);
	from.x += (to & DIR_RIGHT ? inc : 0);
	from.y += (to & DIR_UP ? -inc : 0);
	from.y += (to & DIR_DOWN ? inc : 0);
	return from;
}

void	point_print(point_t point)
{
	printf("(%d,%d)\n", point.x, point.y);
}
