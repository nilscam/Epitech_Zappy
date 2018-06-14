/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_sound.c
*/

#include "map.h"
#include "math_utils.h"

static point_t	calculate_vec_front(point_t from, point_t to)
{
	point_t	dir_front = { to.x - from.x, to.y - from.y };

	return dir_front;
}

static int	map_smallest_x(map_t *map, point_t from, point_t to)
{
	int x_direct = to.x - from.x;
	int inc_x = x_direct > 0 ? -1 : 1;
	point_t	dir = { 0, 0 };

	while (map_is_in_map(map, from)) {
		from.x += inc_x;
		dir.x += inc_x;
	}
	from = map_content_at(map, from)->pos;
	dir = point_add(dir, calculate_vec_front(from, to));
	return abs(dir.x) < abs(x_direct) ? dir.x : x_direct;
}

static int	map_smallest_y(map_t *map, point_t from, point_t to)
{
	int y_direct = to.y - from.y;
	int inc_y = y_direct > 0 ? -1 : 1;
	point_t	dir = { 0, 0 };

	while (map_is_in_map(map, from)) {
		from.y += inc_y;
		dir.y += inc_y;
	}
	from = map_content_at(map, from)->pos;
	dir = point_add(dir, calculate_vec_front(from, to));
	return abs(dir.y) < abs(y_direct) ? dir.y : y_direct;
}

static point_t	map_smallest(map_t *map, point_t from, point_t to)
{
	point_t	smallest;

	smallest.x = map_smallest_x(map, from, to);
	smallest.y = map_smallest_y(map, from, to);
	return smallest;
}

direction_t	map_dir_sound_from(map_t *self, point_t from, point_t to)
{
	point_t	smallest;
	double	angle;

	from = map_content_at(self, from)->pos;
	to = map_content_at(self, to)->pos;
	if (point_are_equals(from, to))
		return DIR_NONE;
	smallest = map_smallest(self, from, to);
	angle = atan2(-smallest.x, -smallest.y) * 180.0 / M_PI;
	return direction_from_angle(angle);
}
