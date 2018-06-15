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

int			get_width(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_width = atoi(av[++(*i)]);
	if (infos->_width <= 0 || 10000 <= infos->_width) {
		dprintf(2, "Invalid width\n");
		return (0);
	}
	return (1);
}

int			get_height(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_height = atoi(av[++(*i)]);
	if (infos->_height <= 0 || 10000 <= infos->_height) {
		dprintf(2, "Invalid height\n");
		return (0);
	}
	return (1);
}

int			get_max_per_team(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_max_per_team = atoi(av[++(*i)]);
	if (infos->_max_per_team <= 0) {
		dprintf(2, "Invalid max_per_team\n");
		return (0);
	}
	return (1);
}

int			get_freq(t_infos *infos, int *i, int ac, char **av)
{
	if (!(*i + 1 < ac))
		return (0);
	infos->_freq = atoi(av[++(*i)]);
	if (infos->_freq <= 0) {
		dprintf(2, "Invalid freq\n");
		return (0);
	}
	return (1);
}