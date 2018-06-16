/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** timer.c
*/

#include "timer.h"
#include <stdio.h>

static bool	new_timer(timer_t *self,
	__attribute__((unused))va_list *args)
{
	timer_mark(self);
	return true;
}

void	timer_mark(timer_t *self)
{
	if (clock_gettime(CLOCK_REALTIME, &self->ts) < 0)
		perror("clock_gettime");
}

long long	timer_time_since_mark(timer_t *self, timer_type_t type)
{
	struct timespec	now;
	double	elapsed;

	if (clock_gettime(CLOCK_REALTIME, &now) < 0)
		perror("clock_gettime");
	if (type == SECONDS) {
		elapsed = (now.tv_sec - self->ts.tv_sec);
		elapsed += ((now.tv_nsec - self->ts.tv_nsec) / 1E9);
	} else if (type == MILLISECONDS) {
		elapsed = ((now.tv_sec - self->ts.tv_sec) * 1E3);
		elapsed += ((now.tv_nsec - self->ts.tv_nsec) / 1E6);
	} else if (type == MICROSECONDS) {
		elapsed = ((now.tv_sec - self->ts.tv_sec) * 1E6);
		elapsed += ((now.tv_nsec - self->ts.tv_nsec) / 1E3);
	} else {
		elapsed = ((now.tv_sec - self->ts.tv_sec) * 1E9);
		elapsed += (now.tv_nsec - self->ts.tv_nsec);
	}
	return elapsed;
}

static const timer_t	timer_CLASS = {
	{
		sizeof(timer_t),
		"Timer",
		(object_cst_t) new_timer,
		NULL
	},
	{}
};

const class_t	*timer = (class_t *) &timer_CLASS;
