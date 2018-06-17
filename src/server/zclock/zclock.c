/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** zclock.c
*/

#include "zclock.h"

static bool	new_zclock(zclock_t *self,
	__attribute__((unused))va_list *args)
{
	zclock_mark(self);
	return true;
}

static const zclock_t	ZCLOCK_CLASS = {
	{
		sizeof(zclock_t),
		"zClock",
		(object_cst_t) new_zclock,
		NULL
	},
	{}
};

const class_t	*ZCLOCK = (class_t *) &ZCLOCK_CLASS;
