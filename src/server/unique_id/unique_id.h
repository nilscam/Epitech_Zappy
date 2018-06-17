/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** unique_id.h
*/

#ifndef unique_id_HPP
#define unique_id_HPP

#include <stddef.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef enum
{
	SEED_PLAYER,
	SEED_EGG,
	SEED_ITEM
}	unique_id_seed_t;

typedef struct
{
	unique_id_seed_t	seed;
	long long		id;
}	unique_id_t;

/* unique_id.c */
long long	unique_id(unique_id_seed_t seed);

#endif // !unique_id_HPP
