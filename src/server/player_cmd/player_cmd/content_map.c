/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** content_map.c
*/

#include "player_cmd.h"
#include "player_callback.h"
#include "debug.h"
#include "player.h"

void	spectate_cmd_content_map(player_cmd_arg_t *args)
{
	map_t	*map = args->server->map;

	for (int y = 0; y < map->size.y; ++y) {
		for (int x = 0; x < map->size.x; ++x) {
			show_content_tile(args->client, map,
				(point_t){ x, y });
		}
	}
}
