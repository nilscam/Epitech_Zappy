/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_timer.c
*/

#include "timer.h"
#include <unistd.h>
#include <stdio.h>

static void	tick(timer_t *c)
{
	printf("timer = %llds %lldms %lldus %lldns\n",
		timer_time_since_mark(c, SECONDS),
		timer_time_since_mark(c, MILLISECONDS),
		timer_time_since_mark(c, MICROSECONDS),
		timer_time_since_mark(c, NANOSECONDS));
}

int	test_timer(void)
{
	timer_t	c;

	INIT(timer, c);
	timer_mark(&c);
	sleep(1);
	tick(&c);
	sleep(1);
	tick(&c);
	sleep(1);
	tick(&c);
	sleep(1);
	tick(&c);
	DEINIT(c);
	return 0;
}
