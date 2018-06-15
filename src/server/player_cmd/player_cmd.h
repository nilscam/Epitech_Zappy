/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_cmd.h
*/

#ifndef player_cmd_HPP
#define player_cmd_HPP

#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef struct
{
	const struct s_player_cmd	*c;
	char				*cmd;
	char				**args;
}	player_cmd_arg_t;

typedef void	(*pl_cmd_fct_t)(player_cmd_arg_t *, va_list *);

typedef struct s_player_cmd
{
	char		*cmd;
	pl_cmd_fct_t	fct;
	int		time_limit;
	size_t		nb_args;
	char		*prototype;
	char		*description;
}	player_cmd_t;

/* player_cmd.c */
bool	player_cmd(char *cmd, ...);
bool	spectate_cmd(char *cmd, ...);

#endif // !player_cmd_HPP
