/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.c
*/

#include "map.h"
#include "list.h"
#include "debug.h"

#include <stdio.h>

void	clear_list(void *data)
{
	printf("clear: %s\n", (char *)data);
}

int	main(void)
{
	// map_t *map = new(MAP, 2, 2);
	// if (!map)
	// 	return (84);
	// printf("map_size : %d,%d\n", map->size.x, map->size.y);
	// for (int y = 0; y < map->size.y; ++y) {
	// 	for (int x = 0; x < map->size.x; ++x) {
	// 		printf("map_content at %d,%d\n",
	// 			map->cases[y][x].pos.x,
	// 			map->cases[y][x].pos.y);
	// 	}
	// }
	// delete(map);
	DEBUG("yolo");
	list_t *list = new(LIST);
	if (!list)
		return (84);
	list_push_back(list, "aaa");
	list_push_back(list, "bbb");
	list_push_back(list, "ccc");
	list_push_front(list, "ddd");
	list_clear(list, clear_list);
	delete(list);
	return 0;
}
