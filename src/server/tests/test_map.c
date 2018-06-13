/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_map.c
*/

#include "map.h"
#include <stdio.h>

void	test_map(void)
{
	printf("test_map\n");
	map_t *map = new(MAP, 2, 2);
	if (!map)
		return;
	printf("map_size : %d,%d\n", map->size.x, map->size.y);
	for (int y = 0; y < map->size.y; ++y) {
		for (int x = 0; x < map->size.x; ++x) {
			printf("map_content at %d,%d\n",
				map->cases[y][x].pos.x,
				map->cases[y][x].pos.y);
		}
	}
	list_push_back(map->players, "yolo");
	list_iterator_t *it = new(LIST_IT, map->players);
	while (it && list_it_can_iterate(it)) {
		printf("--> '%s'\n", (char*)list_it_get(it));
		list_it_iterate(it);
	}
	delete(it);
	delete(map);
}
