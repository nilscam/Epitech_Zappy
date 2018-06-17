/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** egg.c
*/

#include "egg.h"
#include "unique_id.h"

static bool	new_egg(egg_t *self, va_list *args)
{
	self->map = va_arg(*args, map_t *);
	self->pos = va_arg(*args, map_content_t *);
	self->team = va_arg(*args, team_t *);
	self->id = unique_id(SEED_EGG);
	return true;
}

static const egg_t	EGG_CLASS = {
	{
		sizeof(egg_t),
		"egg",
		(object_cst_t) new_egg,
		NULL
	},
	NULL,
	NULL,
	NULL,
	HATCH_TIME,
	0
};

const class_t	*EGG = (class_t *) &EGG_CLASS;
