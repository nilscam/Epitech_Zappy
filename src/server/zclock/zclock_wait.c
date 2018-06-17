/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** zclock_wait.c
*/

#include "zclock.h"

static const double UNITS[] = { 1E6, 1E3, 1, 1E-3 };

void	zclock_wait(long long nb, zclock_type_t type)
{
	for (size_t i = 0; i < SIZE_ARRAY(UNITS); ++i) {
		if (type != i)
			continue;
		usleep(nb * UNITS[i]);
		break;
	}
}
