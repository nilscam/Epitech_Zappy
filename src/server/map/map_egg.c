/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map_egg.c
*/

#include "map.h"
#include "egg.h"

void	map_add_egg_at(map_t *self, team_t *team, point_t pos)
{
	egg_t *egg = NEW(EGG, self, map_content_at(self, pos), team);

	if (egg) {
		list_push_back(self->eggs, egg);
	}
}
