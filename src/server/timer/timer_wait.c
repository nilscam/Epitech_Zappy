/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** timer_wait.c
*/

#include "timer.h"

static const double UNITS[] = { 1E6, 1E3, 1, 1E-3 };

void	timer_wait(long long nb, timer_type_t type)
{
	for (size_t i = 0; i < SIZE_ARRAY(UNITS); ++i) {
		if (type != i)
			continue;
		usleep(nb * UNITS[i]);
		break;
	}
}
