/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** tests.c
*/

#include "debug.h"

int	test_list(void);
int	test_map(void);
int	test_map_it(void);
int	test_player(void);
int 	test_vision(void);
int	test_map_sound(void);
int	test_tcp_connection(int ac, char **av);
int	test_player_cmd(void);
int	test_parsing(int ac, char **av);
int	test_list_extract(void);
int	test_zclock(void);
int	test_unique_id(void);
int	test_big_buff(void);
int	test_list_alloc(void);

int	tests(
	__attribute__((unused))int ac,
	__attribute__((unused))char **av)
{
	// return test_list();
	// return test_player();
	// return test_map();
	// return test_map_it();
	// return test_vision();
	// return test_map_sound();
	// return test_tcp_connection(ac, av);
	// return test_player_cmd();
	return test_parsing(ac, av);
	// return test_list_extract();
	// return test_zclock();
	// return test_unique_id();
	// return test_big_buff();
	// return test_list_alloc();
	return 0;
}
