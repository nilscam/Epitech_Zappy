/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction.c
*/

#include "direction.h"
#include "math_utils.h"
#include <stdio.h>
#include <string.h>

static const struct circle_direction_s	CIRCLES[] = {
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

char	*direction_repr(direction_t dir)
{
	char	buff[255];
	char	*tmp = buff;

	if (dir & DIR_LEFT)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Left");
	if (dir & DIR_RIGHT)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Right");
	if (dir & DIR_UP)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Up");
	if (dir & DIR_DOWN)
		tmp += sprintf(tmp, "%s%s", tmp > buff ? "," : "", "Down");
	if (tmp <= buff)
		tmp += sprintf(tmp, "%s", "None");
	return tmp <= buff ? NULL : strdup(buff);
}

direction_t	direction_turn_left(direction_t dir)
{
	if (dir & (DIR_LEFT | DIR_RIGHT))
		return dir & DIR_LEFT ? DIR_DOWN : DIR_UP;
	else if (dir & (DIR_UP | DIR_DOWN))
		return dir & DIR_UP ? DIR_LEFT : DIR_RIGHT;
	return dir;
}

direction_t	direction_turn_right(direction_t dir)
{
	if (dir & (DIR_LEFT | DIR_RIGHT))
		return dir & DIR_LEFT ? DIR_UP : DIR_DOWN;
	else if (dir & (DIR_UP | DIR_DOWN))
		return dir & DIR_UP ? DIR_RIGHT : DIR_LEFT;
	return dir;
}

direction_t	direction_from_angle(double d)
{
	const struct circle_direction_s	*c = NULL;
	int max_c = sizeof(CIRCLES) / sizeof(struct circle_direction_s);

	d = to_valid_angle(d);
	for (int i = 0; i < max_c; ++i) {
		c = &CIRCLES[i];
		if (c->min <= d && d <= c->max) {
			return c->dir;
		}
	}
	return DIR_NONE;
}
