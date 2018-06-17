/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** test_unique_id.c
*/

#include "unique_id.h"
#include "stdio.h"

int	test_unique_id(void)
{
	printf("SEED_PLAYER id = %lld\n", unique_id(SEED_PLAYER));
	printf("SEED_PLAYER id = %lld\n", unique_id(SEED_PLAYER));
	printf("SEED_EGG id = %lld\n", unique_id(SEED_EGG));
	printf("SEED_ITEM id = %lld\n", unique_id(SEED_ITEM));
	printf("SEED_PLAYER id = %lld\n", unique_id(SEED_PLAYER));
	return 0;
}
