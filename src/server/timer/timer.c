/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** timer.c
*/

#include "timer.h"

static bool	new_timer(timer_t *self,
	__attribute__((unused))va_list *args)
{
	timer_mark(self);
	return true;
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
