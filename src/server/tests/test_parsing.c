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

	help(av[0]);
	if (!infos._err)
		return (84);
	printf("Help: %d\n", infos._is_help);
	printf("Port: %d\n", infos._port);
	printf("Width: %d\n", infos._width);
	printf("Height: %d\n", infos._height);
	printf("MaxPerTeam: %d\n", infos._max_per_team);
	printf("Freq: %d\n", infos._freq);
	printf("TeamName:\n");
	for (int i = -1; infos._team_name && infos._team_name[++i];) {
		printf("[%s]\n", infos._team_name[i]);
	}
	return (0);
}