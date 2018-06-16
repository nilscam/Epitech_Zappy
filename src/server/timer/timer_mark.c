/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** timer_mark.c
*/

#include "timer.h"

static const double UNITS[] = {
	1, 1E9,
	1E3, 1E6,
	1E6, 1E3,
	1E9, 1
};

void	timer_mark(timer_t *self)
{
	if (clock_gettime(CLOCK_REALTIME, &self->ts) < 0)
		perror("clock_gettime");
}

long long	timer_time_since_mark(timer_t *self, timer_type_t type)
{
	struct timespec	n;
	long long	t = 0;

	if (clock_gettime(CLOCK_REALTIME, &n) < 0)
		perror("clock_gettime");
	for (size_t i = 0; i < SIZE_ARRAY(UNITS) / 2; ++i) {
		if (type != i)
			continue;
		t = ((n.tv_sec - self->ts.tv_sec) * UNITS[i * 2]);
		t += ((n.tv_nsec - self->ts.tv_nsec) / UNITS[i * 2 + 1]);
		break;
	}
	return t;
}
