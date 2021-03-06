/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include <utils/point.h>
#include <list/list.h>
#include "map.h"

void	fill_inv_ptrs(inventory_t *inv, int **ptrs)
{
	ptrs[0] = &inv->food;
	ptrs[1] = (int *)&inv->stones[LINEMATE];
	ptrs[2] = (int *)&inv->stones[DERAUMERE];
	ptrs[3] = (int *)&inv->stones[SIBUR];
	ptrs[4] = (int *)&inv->stones[MENDIANE];
	ptrs[5] = (int *)&inv->stones[PHIRAS];
	ptrs[6] = (int *)&inv->stones[THYSTAME];
}

void	fill_inv_reprs(char **reprs)
{
	reprs[0] = "food";
	reprs[1] = "linemate";
	reprs[2] = "deraumere";
	reprs[3] = "sibur";
	reprs[4] = "mendiane";
	reprs[5] = "phiras";
	reprs[6] = "thystame";
}

void init_map_inventory(inventory_t *inv, inventory_t *map_inv)
{
	int res;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		if (map_inv->stones[i] > 0 && rand() % 8 < 2) {
			res = (rand() % 2) % map_inv->stones[i];
			inv->stones[i] += res;
			map_inv->stones[i] -= res;
		}
	}
	if (map_inv->food > 0 && rand() % 8 > 2) {
		res = (rand() % 2) % map_inv->food;
		inv->food += res;
		map_inv->food -= res;
	}
}

void	init_player_inventory(inventory_t *inv)
{
	inv->food = 10;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		inv->stones[i] = 0;
	}
}

void	empty_stones_inventory(inventory_t *inv)
{
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		inv->stones[i] = 0;
	}
}
