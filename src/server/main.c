/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.c
*/

#include "map.h"
#include <stdio.h>

int	main(void)
{
	map_t *map = new(MAP, 2, 2);
	if (!map)
		return (84);
	printf("map_size : %d,%d\n", map->size.x, map->size.y);
	for (int y = 0; y < map->size.y; ++y) {
		for (int x = 0; x < map->size.x; ++x) {
			printf("map_content at %d,%d\n",
				map->cases[y][x].pos.x,
				map->cases[y][x].pos.y);
		}
	}
	delete(map);
	return 0;
}
