/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_map.c
*/

#include "map.h"
#include "map_it.h"
#include <stdio.h>

void	keep_switching(size_t i)
{
	switch (i) {
	case MENDIANE:
		printf("Mendiane : ");
		break;
	case PHIRAS:
		printf("Phiras : ");
		break;
	case THYSTAME:
		printf("Thystame : ");
		break;
	default:
		break;
	}
}

void	switcheroo(size_t i)
{
	switch (i) {
	case LINEMATE:
		printf("Linemate : ");
		break;
	case DERAUMERE:
		printf("Deraumere : ");
		break;
	case SIBUR :
		printf("Sibur : ");
		break;
	default:
		keep_switching(i);
	}
}

void	print_map_content(map_t *map)
{
	printf("map_size : %d,%d\n", map->size.x, map->size.y);
	for (int y = 0; y < map->size.y; ++y) {
		for (int x = 0; x < map->size.x; ++x) {
			printf("map_content at %d,%d\n",
				map->cases[y][x].pos.x,
				map->cases[y][x].pos.y);
			printf("\tStones\n");
			for (size_t i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
				printf("\t\t");
				switcheroo(i);
				printf("\t%d\n", map->cases[y][x].inventory.stones[i]);
			}
			printf("\n\tFood");
			printf("\t\t\t%d\n", map->cases[y][x].inventory.food);
		}
	}
}

int	test_map(void)
{
	map_t *map = NEW(MAP, 10, 10);
	if (!map)
		return 84;
	print_map_content(map);
	list_push_back(map->players, "yolo");
	list_iterator_t *it = NEW(LIST_IT, map->players);
	while (it && list_it_can_iterate(it)) {
		printf("--> player : '%s'\n", (char*)list_it_get(it));
		list_it_iterate(it);
	}
	inventory_t inv;

	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i)
		inv.stones[i] = 0;
	count_inv_in_map(map, &inv);
	for (int i = 0 ; i < NUMBER_OF_INV_TYPE ; ++i) {
		i == LINEMATE ? printf("linemate %d\n", inv.stones[i]) : 0;
		i == DERAUMERE ? printf("deraumere %d\n", inv.stones[i]) : 0;
		i == SIBUR ? printf("sibur %d\n", inv.stones[i]) : 0;
		i == MENDIANE ? printf("mendiane %d\n", inv.stones[i]) : 0;
		i == PHIRAS ? printf("phiras %d\n", inv.stones[i]) : 0;
		i == THYSTAME ? printf("thystame %d\n", inv.stones[i]) : 0;
	}
	return 0;
}
