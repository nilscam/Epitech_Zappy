/*
** EPITECH PROJECT, 2018
** get_infos
** File description:
** get_infos
*/

#include "parsing.h"

int			get_port(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_port = atoi(av[++(*i)]);
	if (infos->_port <= 0 || 65537 <= infos->_port) {
		dprintf(2, "Invalid port number\n");
		return (0);
	}
	return (1);
}

int			get_name(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_name = strdup(av[++(*i)]);
	if (!infos->_name) {
		dprintf(2, "Invalid name\n");
		return (0);
	}
	return (1);
}

int			get_machine(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_machine = strdup(av[++(*i)]);
	if (!infos->_machine) {
		dprintf(2, "Invalid machine\n");
		return (0);
	}
	return (1);
}