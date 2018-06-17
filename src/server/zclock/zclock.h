/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** zclock.h
*/

#ifndef zclock_HPP
#define zclock_HPP

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
}	zclock_type_t;

typedef struct
{
	class_t		__base__;
	struct timespec	ts;
}	zclock_t;

/* zclock_mark.c */
void		zclock_mark(zclock_t *self);
long long	zclock_time_since_mark(zclock_t *self, zclock_type_t type);

/* zclock_wait.c */
void		zclock_wait(long long nb, zclock_type_t type);

/* zclock.c */
extern const class_t *ZCLOCK;

#endif // !zclock_HPP
