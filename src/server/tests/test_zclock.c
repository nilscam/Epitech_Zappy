/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_zclock.c
*/

#include "zclock.h"
#include <unistd.h>
#include <stdio.h>

static void	show_time_since_mark(zclock_t *c)
{
	printf("zclock = %llds %lldms %lldus %lldns\n",
		zclock_time_since_mark(c, SECONDS),
		zclock_time_since_mark(c, MILLISECONDS),
		zclock_time_since_mark(c, MICROSECONDS),
		zclock_time_since_mark(c, NANOSECONDS));
}

int	test_zclock(void)
{
	zclock_t	c;

	INIT(ZCLOCK, c);
	zclock_mark(&c);
	zclock_wait(1, SECONDS);
	show_time_since_mark(&c);
	zclock_wait(1E3, MILLISECONDS);
	show_time_since_mark(&c);
	zclock_wait(1E6, MICROSECONDS);
	show_time_since_mark(&c);
	zclock_wait(1E9, NANOSECONDS);
	show_time_since_mark(&c);
	DEINIT(c);
	return 0;
}
