/*
** EPITECH PROJECT, 2018
** parsing
** File description:
** parsing
*/

#ifndef PARSING_H_
# define PARSING_H_

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef struct	s_infos		t_infos;

struct 				s_infos
{
	bool				_is_help;
	int				_port;
	int				_width;
	int				_height;
	int				_max_per_team;
	int				_freq;
	char			**_team_name;
	int				_err;
};

typedef struct
{
	char	*flag;
	int	size;
	int	(*fct)(t_infos *, int *, int, char **);
}	parsing_info_t;

bool	check_is_help(int ac, char **av);
int	help(char *self);

int	get_port(t_infos *infos, int *i, int ac, char **av);
int	get_width(t_infos *infos, int *i, int ac, char **av);
int	get_height(t_infos *infos, int *i, int ac, char **av);
int	get_max_per_team(t_infos *infos, int *i, int ac, char **av);
int	get_freq(t_infos *infos, int *i, int ac, char **av);

int		get_team_name(t_infos *infos, int *i, int ac, char **av);
void		init_infos(t_infos *infos);
void		parse_info(t_infos *infos, int *i, int ac, char **av);
t_infos		parse_args(int ac, char **av);

#endif /* PARSING_H_ */