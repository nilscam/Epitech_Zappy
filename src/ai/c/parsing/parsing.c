/*
** EPITECH PROJECT, 2018
** parsing
** File description:
** parsing
*/

#include "parsing.h"

void		init_infos(t_infos *infos)
{
	infos->_port = 0;
	infos->_err = 0;
	infos->_name = NULL;
	infos->_machine = NULL;
}

void		parse_info(t_infos *infos, int *i, int ac, char **av)
{
	infos->_err = 0;
	if (!strncmp(av[*i], "-p", 2))
		infos->_err = get_port(infos, i, ac, av);
	else if (!strncmp(av[*i], "-n", 2))
		infos->_err = get_name(infos, i, ac, av);
	else if (!strncmp(av[*i], "-h", 2))
		infos->_err = get_machine(infos, i, ac, av);
}

t_infos		parse_args(int ac, char **av)
{
	t_infos	infos;

	init_infos(&infos);
	for (int i = 1; i < ac; ++i) {
		parse_info(&infos, &i, ac, av);
		if (!infos._err)
			return (infos);
	}
	infos._err = 1;
	return (infos);
}