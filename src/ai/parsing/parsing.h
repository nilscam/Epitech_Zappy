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

typedef struct	s_infos		t_infos;

struct 				s_infos
{
	int				_port;
	char			*_name;
	char			*_machine;
	int				_err;
};

//				help.c
int	help(void);

//				get_infos.c
int			get_port(t_infos *infos, int *i, int ac, char **av);
int			get_name(t_infos *infos, int *i, int ac, char **av);
int			get_machine(t_infos *infos, int *i, int ac, char **av);

//				parsing.c
void		init_infos(t_infos *infos);
void		parse_info(t_infos *infos, int *i, int ac, char **av);
t_infos		parse_args(int ac, char **av);

#endif /* PARSING_H_ */