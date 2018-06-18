/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_map_sound.c
*/

#include "map.h"
#include <stdio.h>

static void	assert_dir(map_t *map, point_t from,
	point_t to, direction_t dir)
{
	static int count = 0;
	direction_t res = map_dir_sound_from(map, from, to);

	++count;
	if (res != dir) {
		dprintf(2, "assert_dir %d: expected: %s, got: %s\n",
			count, direction_repr(dir), direction_repr(res));
		exit(1);
	}
}

static void	assert_valid_dirs(map_t *map, point_t to, int inc)
{
	assert_dir(map, (point_t){ to.x - inc, to.y - inc }, to,
		DIR_UP | DIR_LEFT);
	assert_dir(map, (point_t){ to.x, to.y - inc }, to,
		DIR_UP);
	assert_dir(map, (point_t){ to.x + inc, to.y - inc }, to,
		DIR_UP | DIR_RIGHT);
	assert_dir(map, (point_t){ to.x - inc, to.y }, to,
		DIR_LEFT);
	assert_dir(map, (point_t){ to.x, to.y }, to,
		DIR_NONE);
	assert_dir(map, (point_t){ to.x + inc, to.y }, to,
		DIR_RIGHT);
	assert_dir(map, (point_t){ to.x - inc, to.y + inc }, to,
		DIR_DOWN | DIR_LEFT);
	assert_dir(map, (point_t){ to.x, to.y + inc }, to,
		DIR_DOWN);
	assert_dir(map, (point_t){ to.x + inc, to.y + inc }, to,
		DIR_DOWN | DIR_RIGHT);
}

int	test_map_sound(void)
{
	int	players_per_team = 12;
	map_t *map = NEW(MAP, 10, 11, players_per_team);
	if (!map)
		return 84;
	assert_valid_dirs(map, (point_t){1, 1}, 1);
	assert_valid_dirs(map, (point_t){1, 1}, 2);
	assert_valid_dirs(map, (point_t){1, 1}, 3);
	assert_valid_dirs(map, (point_t){1, 1}, 4);
	assert_dir(map, (point_t){ 2, 9 }, (point_t){ 5, 2 }, DIR_UP | DIR_LEFT);
	assert_dir(map, (point_t){ 5, 2 }, (point_t){ 2, 9 }, DIR_DOWN | DIR_RIGHT);
	printf("test_map_sounds: OK\n");
	DELETE(map);
	return 0;
}
