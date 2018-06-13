/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** inventory.c
*/

#include "map.h"

void	init_map_inventory(inventory_t *inv)
{
	inv->food = rand() % 2;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		//		inv->stones[i] = 0;
		inv->stones[i] = rand() % 2;
	}
}

void	init_player_inventory(inventory_t *inv)
{
	inv->food = 126;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		inv->stones[i] = 0;
	}
}
