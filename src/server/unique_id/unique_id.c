/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** unique_id.c
*/

#include "unique_id.h"

long long	unique_id(unique_id_seed_t seed)
{
	static unique_id_t	ids[] = { { 0, 0 }, { 1, 0, }, { 2, 0 } };

	for (size_t i = 0; i < SIZE_ARRAY(ids); ++i) {
		if (seed == ids[i].seed) {
			return ++ids[i].id;
		}
	}
	return 0;
}
