/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_map.c
*/

#include "map.h"
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
	map_t *map = new(MAP, 2, 2);
	if (!map)
		return 84;
	print_map_content(map);
	list_push_back(map->players, "yolo");
	list_iterator_t *it = new(LIST_IT, map->players);
	while (it && list_it_can_iterate(it)) {
		printf("--> player : '%s'\n", (char*)list_it_get(it));
		list_it_iterate(it);
	}
	delete(it);
	delete(map);
	return 0;
}
