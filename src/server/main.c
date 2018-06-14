/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** main.c
*/

#include "debug.h"
#include <time.h>
#include <stdlib.h>

int	test_list(void);
int	test_map(void);
int	test_map_it(void);
int	test_player(void);
int 	test_vision(void);

int	main(void)
{
	srand((unsigned int)time(NULL));
	// return test_list();
	// return test_player();
	// return test_map();
	// return test_map_it();
	test_vision();
	return 0;
}
