/*
** EPITECH PROJECT, 2018
** parsing
** File description:
** parsing
*/

#include "parsing.h"

int			get_team_name(t_infos *infos, int *i, int ac, char **av)
{
	int		start = *i, end = 0, idx_tab = -1;

	while (++(*i) < ac && strncmp(av[*i], "-p", 2)
			&& strncmp(av[*i], "-x", 2)
			&& strncmp(av[*i], "-y", 2)
			&& strncmp(av[*i], "-c", 2)
			&& strncmp(av[*i], "-f", 2))
			++end;
	if (!end) {
		dprintf(2, "Invalid Team Name\n");
		return (0);
	}
	infos->_team_name = malloc(sizeof(char *) * (end + 1));
	while (--end > -1)
		infos->_team_name[++idx_tab] = strdup(av[++start]);
	infos->_team_name[++idx_tab] = NULL;
	--(*i);
	return (1);
}

void		init_infos(t_infos *infos)
{
	infos->_port = 0;
	infos->_width = 0;
	infos->_height = 0;
	infos->_max_per_team = 0;
	infos->_freq = 0;
	infos->_err = 0;
	infos->_team_name = NULL;
}

void		parse_info(t_infos *infos, int *i, int ac, char **av)
{
	infos->_err = 0;
	if (!strncmp(av[*i], "-p", 2))
		infos->_err = get_port(infos, i, ac, av);
	else if (!strncmp(av[*i], "-x", 2))
		infos->_err = get_width(infos, i, ac, av);
	else if (!strncmp(av[*i], "-y", 2))
		infos->_err = get_height(infos, i, ac, av);
	else if (!strncmp(av[*i], "-n", 2))
		infos->_err = get_team_name(infos, i, ac, av);
	else if (!strncmp(av[*i], "-c", 2))
		infos->_err = get_max_per_team(infos, i, ac, av);
	else if (!strncmp(av[*i], "-f", 2))
		infos->_err = get_freq(infos, i, ac, av);
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