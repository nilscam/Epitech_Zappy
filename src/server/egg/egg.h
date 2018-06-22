/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** egg.h
*/

#ifndef egg_HPP
#define egg_HPP

#define HATCH_TIME	600

#include "class.h"
#include "map.h"

typedef struct
{
	class_t		__base__;
	map_t		*map;
	map_content_t	*pos;
	team_t		*team;
	int		remaining_time_units;
	long long	id;
}	egg_t;

/* egg_hatch.c */
void	egg_wait(egg_t *self);
bool	egg_is_hatched(egg_t *self);
bool	egg_will_hatch(egg_t *self);

/* egg.c */
extern const class_t *EGG;

#endif // !egg_HPP
