/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_utils.c
*/

#include "player.h"
#include <stdio.h>

void	player_print(player_t *self)
{
	char	*repr = direction_repr(self->dir);
	printf("Player '%s' is in team '%s' at (%d,%d) looking at %s",
		self->name, self->team,
		self->pos->pos.x, self->pos->pos.y,
		repr);
	printf(" [%dF %dL %dD %dS %dM %dP %dT]\n",
		self->inventory.food,
		self->inventory.stones[LINEMATE],
		self->inventory.stones[DERAUMERE],
		self->inventory.stones[SIBUR],
		self->inventory.stones[MENDIANE],
		self->inventory.stones[PHIRAS],
		self->inventory.stones[THYSTAME]);
	SAFE_FREE(&repr);
}
