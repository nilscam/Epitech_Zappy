/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction.c
*/

#include "direction.h"
#include <stdio.h>
#include <string.h>

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
