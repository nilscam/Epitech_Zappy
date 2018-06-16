/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** timer.h
*/

#ifndef timer_HPP
#define timer_HPP

#include "class.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef enum
{
	SECONDS,
	MILLISECONDS,
	MICROSECONDS,
	NANOSECONDS
}	timer_type_t;

typedef struct
{
	class_t		__base__;
	struct timespec	ts;
}	timer_t;

/* timer_mark.c */
void		timer_mark(timer_t *self);
long long	timer_time_since_mark(timer_t *self, timer_type_t type);

/* timer_wait.c */
void		timer_wait(long long nb, timer_type_t type);

/* timer.c */
extern const class_t *timer;

#endif // !timer_HPP
