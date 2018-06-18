/*
** EPITECH PROJECT, 2018
** main
** File description:
** main
*/

#include "parsing.h"

int	test_parsing(int ac, char **av)
{
	t_infos	infos = parse_args(ac, av);

	if (!infos._err)
		return (84);
	printf("Port: %d\n", infos._port);
	printf("Name: %s\n", infos._name);
	printf("Machine: %s\n", infos._machine);
	return (0);
}