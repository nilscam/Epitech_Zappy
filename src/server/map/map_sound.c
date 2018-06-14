/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_sound.c
*/

#include "map.h"

static const struct circle_direction_s	CIRCLES[] = {
	// { 0.0, 22.5, DIR_RIGHT },
	// { 22.5, 67.5, DIR_RIGHT | DIR_UP },
	// { 67.5, 112.5, DIR_UP },
	// { 112.5, 157.5, DIR_UP | DIR_LEFT },
	// { 157.5, 202.5, DIR_LEFT },
	// { 202.5, 247.5, DIR_LEFT | DIR_DOWN },
	// { 247.5, 292.5, DIR_DOWN },
	// { 292.5, 337.5, DIR_DOWN | DIR_RIGHT },
	// { 337.5, 360.0, DIR_RIGHT }
	{ 0.0, 22.5, DIR_DOWN },
	{ 22.5, 67.5, DIR_DOWN | DIR_RIGHT },
	{ 67.5, 112.5, DIR_RIGHT },
	{ 112.5, 157.5, DIR_RIGHT | DIR_UP },
	{ 157.5, 202.5, DIR_UP },
	{ 202.5, 247.5, DIR_UP | DIR_LEFT },
	{ 247.5, 292.5, DIR_LEFT },
	{ 292.5, 337.5, DIR_LEFT | DIR_DOWN },
	{ 337.5, 360.0, DIR_DOWN }
};

#include "debug.h" //!tmp
#include <stdio.h> //!tmp
#include <math.h>

static double	dmod(double a, double b)
{
	return b == 0 ? 0 : a - b * floor(a / b);
}

static double	to_valid_angle(double d)
{
	d = dmod(d, 360);
	while (d < 0)
		d += 360.0;
	return d;
}

static direction_t	dir_from_angle(double d)
{
	const struct circle_direction_s	*c = NULL;
	int max_c = sizeof(CIRCLES) / sizeof(struct circle_direction_s);

	d = to_valid_angle(d);
	for (int i = 0; i < max_c; ++i) {
		c = &CIRCLES[i];
		if (c->min <= d && d <= c->max) {
			// printf("%f <= %f <= %f\n", c->min, d, c->max);
			return c->dir;
		}
	}
	return DIR_NONE;
}

static point_t	calculate_vec_front(point_t from, point_t to)
{
	point_t	dir_front = { to.x - from.x, to.y - from.y };

	return dir_front;
}

static point_t	calculate_vec_back(map_t *map, point_t from, point_t to)
{
	point_t	dir_front = calculate_vec_front(from, to);
	point_t dir_back = { 0, 0 };
	int inc_x = dir_front.x > 0 ? 1 : -1;
	int inc_y = dir_front.y > 0 ? -1 : 1;
	point_t new_pos;

	if (abs(dir_front.y) > abs(dir_front.x)) {
		// DEBUG("y > x ---> go to y (%d)", inc_y);
		while (map_is_in_map(map, from)) {
			from.y += inc_y;
			dir_back.y += inc_y;
			// printf("...y + %d...", inc_y);point_print(from);
		}
	} else {
		// DEBUG("x >= y ---> go to x (%d)", inc_x);
		while (map_is_in_map(map, from)) {
			from.x += inc_x;
			dir_back.x += inc_x;
			// printf("...x + %d...", inc_x);point_print(from);
		}
	}
	new_pos = map_content_at(map, from)->pos;
	// printf("dir_back: ");point_print(dir_back);
	// printf("new_pos:  ");point_print(new_pos);
	dir_back.x += inc_x * abs(to.x - new_pos.x);
	dir_back.y += inc_y * abs(to.y - new_pos.y);
	// printf("dir_back: ");point_print(dir_back);
	return dir_back;
}

static int	point_distance(point_t point)
{
	return abs(point.x) + abs(point.y);
}

direction_t	map_dir_sound_from(map_t *self, point_t from, point_t to)
{
	if (point_are_equals(from, to))
		return DIR_NONE;
	point_t	vec_front = calculate_vec_front(from, to);
	point_t	vec_back = calculate_vec_back(self, from, to);
	// printf("from     : ");point_print(from);
	// printf("to       : ");point_print(to);
	// printf("vec_front: ");point_print(vec_front);
	// printf("vec_back : ");point_print(vec_back);
	int df = point_distance(vec_front);
	int db = point_distance(vec_back);
	// DEBUG("df %d <-> db %d", df, db);
	point_t smaller_vec = (df < db ? vec_front : vec_back);
	// printf("smaller  : ");point_print(smaller_vec);
	double angle = atan2(-smaller_vec.x, -smaller_vec.y) * 180.0 / M_PI;
	direction_t dir = dir_from_angle(angle);
	// printf("angle %f --> dir %d (%s)\n", angle, dir, direction_repr(dir));
	return dir;
}
