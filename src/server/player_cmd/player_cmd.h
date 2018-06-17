/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_cmd.h
*/

#ifndef player_cmd_HPP
#define player_cmd_HPP

#include "server.h"
#include "player.h"
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>

#define SIZE_ARRAY(x)	(sizeof(x) / sizeof(*x))

typedef struct
{
	const struct s_player_cmd	*c;
	char				*cmd;
	char				**args;
	int				nb_args;
	client_t			*client;
	t_server			*server;
	player_t			*player;
}	player_cmd_arg_t;

typedef void	(*pl_cmd_fct_t)(player_cmd_arg_t *);

typedef struct s_player_cmd
{
	char		*cmd;
	pl_cmd_fct_t	fct;
	int		time_limit;
	int		nb_args;
	char		*prototype;
	char		*description;
}	player_cmd_t;

/* player_cmd.c */
bool	client_cmd(t_server *, client_t *, char *cmd, player_t *);

/* player_cmd/cmds.c */
void	anonymous_cmd_anonymous(player_cmd_arg_t *args);
void	anonymous_cmd_spectator(player_cmd_arg_t *args);
void	player_cmd_error(player_cmd_arg_t *args);
void	player_cmd_forward(player_cmd_arg_t *args);
void	player_cmd_right(player_cmd_arg_t *args);
void	player_cmd_left(player_cmd_arg_t *args);
void	player_cmd_look(player_cmd_arg_t *args);
void	player_cmd_inventory(player_cmd_arg_t *args);
void	player_cmd_broadcast(player_cmd_arg_t *args);
void	player_cmd_connect_nbr(player_cmd_arg_t *args);
void	player_cmd_fork(player_cmd_arg_t *args);
void	player_cmd_eject(player_cmd_arg_t *args);
void	player_cmd_take(player_cmd_arg_t *args);
void	player_cmd_set_obj_down(player_cmd_arg_t *args);
void	player_cmd_incantation(player_cmd_arg_t *args);
void	spectate_cmd_map_size(player_cmd_arg_t *args);
void	spectate_cmd_map_content_tile(player_cmd_arg_t *args);
void	spectate_cmd_content_map(player_cmd_arg_t *args);
void	spectate_cmd_name_teams(player_cmd_arg_t *args);
void	spectate_cmd_player_pos(player_cmd_arg_t *args);
void	spectate_cmd_player_level(player_cmd_arg_t *args);
void	spectate_cmd_player_inventory(player_cmd_arg_t *args);
void	spectate_cmd_time_unit(player_cmd_arg_t *args);
void	spectate_cmd_time_unit_mod(player_cmd_arg_t *args);

/* player_cmd/map_content_tile.c */
void	show_content_tile(client_t *client, map_t *map, point_t point);

#endif // !player_cmd_HPP
