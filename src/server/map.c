/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** map.c
*/

#include "map.h"

static void	init_inventory(inventory_t *inv)
{
	inv->food = 0;
	for (int i = 0; i < NUMBER_OF_INV_TYPE; ++i) {
		inv->stones[i] = 0;
	}
}

static void	init_map_content(map_content_t *content, point_t pos)
{
	content->pos = pos;
	init_inventory(&content->inventory);
}

static void	init_map_contents(map_t *self)
{
	map_content_t	*content;
	int	size_x = self->size.x;
	int	size_y = self->size.y;

	for (int i = 0; i < size_y; ++i)
		self->cases[i] = self->cases_buff + size_x * i;
	self->cases[size_y] = NULL;
	for (int y = 0; y < size_y; ++y) {
		for (int x = 0; x < size_x; ++x) {
			content = &self->cases[y][x];
			init_map_content(content, (point_t){x, y});
		}
	}
}

static bool	allocate_cases(map_t *self, int x, int y)
{
	self->cases_buff = malloc(sizeof(map_content_t) * (x * y));
	if (!self->cases_buff)
		return false;
	self->cases = malloc(sizeof(map_content_t *) * (y + 1));
	if (!self->cases)
	{
		free(self->cases_buff);
		return false;
	}
	return true;
}

static bool	new_map(map_t *self, va_list *args)
{
	int	x = va_arg(*args, int);
	int	y = va_arg(*args, int);

	self->size.x = x;
	self->size.y = y;
	if (!allocate_cases(self, x, y))
		return false;
	init_map_contents(self);
	return true;
}

static void	delete_map(__attribute__((unused))map_t *self)
{
	SAFE_FREE(&self->cases_buff);
	SAFE_FREE(&self->cases);
}

static const map_t	MAP_CLASS = {
	{
		sizeof(map_t),
		"Map",
		(object_cst_t) new_map,
		(object_dst_t) delete_map
	},
	{
		0,
		0
	},
	NULL,
	NULL
};

const class_t	*MAP = (class_t *) &MAP_CLASS;
