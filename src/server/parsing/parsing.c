/*
** EPITECH PROJECT, 2018
** parsing
** File description:
** parsing
*/

#include "parsing.h"
#include "str_to_tab.h"

static const parsing_info_t	PARSING_INFOS[] = {
	{ "-p", 2, get_port },
	{ "-x", 2, get_width },
	{ "-y", 2, get_height },
	{ "-n", 2, get_team_name },
	{ "-c", 2, get_max_per_team },
	{ "-f", 2, get_freq }
};

static void	check_error(t_infos *i)
{
	if (i->_port <= 0 || i->_width <= 0 || i->_height <= 0
		|| i->_max_per_team <= 0 || i->_freq <= 0
		|| !i->_team_name || !(*i->_team_name))
		i->_err = 0;
}

int	get_team_name(t_infos *infos, int *i, int ac, char **av)
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
	infos->_is_help = false;
	infos->_port = 4242;
	infos->_width = -1;
	infos->_height = -1;
	infos->_max_per_team = -1;
	infos->_freq = 100;
	infos->_err = 0;
	infos->_team_name = NULL;
}

void		parse_info(t_infos *infos, int *i, int ac, char **av)
{
	int max = SIZE_ARRAY(PARSING_INFOS);
	const parsing_info_t *info;

	infos->_err = 0;
	for (int p = 0; p < max; ++p) {
		info = &PARSING_INFOS[p];
		if (!strncmp(av[*i], info->flag, info->size)) {
			infos->_err = info->fct(infos, i, ac, av);
			return;
		}
	}
}

t_infos		parse_args(int ac, char **av)
{
	t_infos	infos;

	init_infos(&infos);
	infos._is_help = check_is_help(ac, av);
	if (infos._is_help)
		return (infos);
	for (int i = 1; i < ac; ++i) {
		parse_info(&infos, &i, ac, av);
		if (!infos._err) {
			free_tab(infos._team_name);
			return (infos);
		}
	}
	infos._err = 1;
	check_error(&infos);
	if (!infos._err)
		free_tab(infos._team_name);
	return (infos);
}