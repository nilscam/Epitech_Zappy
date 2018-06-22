/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** stat.c
*/

#include "map_it.h"

void	remove_inv_from_to(inventory_t *from, inventory_t *to)
{
	to->food += from->food;
	to->stones[LINEMATE] += from->stones[LINEMATE];
	to->stones[DERAUMERE] += from->stones[DERAUMERE];
	to->stones[SIBUR] += from->stones[SIBUR];
	to->stones[MENDIANE] += from->stones[MENDIANE];
	to->stones[PHIRAS] += from->stones[PHIRAS];
	to->stones[THYSTAME] += from->stones[THYSTAME];
}

void	count_inv_in_map(map_t *self, inventory_t *inv)
{
	for (int y = 0; y < self->size.y; ++y) {
		for (int x = 0; x < self->size.x; ++x) {
			remove_inv_from_to(&self->cases[y][x].inventory,
				inv);
		}
	}
}
