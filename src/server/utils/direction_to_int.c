/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** direction_to_int.c
*/

#include "direction.h"
#include <stddef.h>

static const direction_t DIRS_CONVERT[] = {
	DIR_NONE,
	DIR_UP,
	DIR_UP | DIR_LEFT,
	DIR_LEFT,
	DIR_LEFT | DIR_DOWN,
	DIR_DOWN,
	DIR_DOWN | DIR_RIGHT,
	DIR_RIGHT,
	DIR_RIGHT | DIR_UP
};

int	direction_to_int(direction_t dir)
{
	for (size_t i = 0; i < SIZE_ARRAY(DIRS_CONVERT); ++i) {
		if (dir == DIRS_CONVERT[i]) {
			return i;
		}
	}
	return 0;
}

int	direction_to_int_spec(direction_t d)
{
	return d & DIR_UP ? 1 : d & DIR_RIGHT ? 2 : d & DIR_DOWN ? 3 : 4;
}
