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

/* timer.c */
void		timer_mark(timer_t *self);
long long	timer_time_since_mark(timer_t *self, timer_type_t type);

extern const class_t *timer;

#endif // !timer_HPP
