/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_cmd.c
*/

#include "player_cmd.h"
#include <string.h>

void	player_cmd_forward(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_right(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_left(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_look(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_inventory(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_broadcast(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_connect_nbr(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_fork(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_eject(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_take(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_set_obj_down(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	player_cmd_incantation(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_map_size(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_map_content_time(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_content_map(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_name_teams(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_player_pos(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_player_level(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_player_inventory(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_time_unit(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}
void	spectate_cmd_time_unit_mod(player_cmd_arg_t *args, va_list *vargs){(void)args;(void)vargs;}

static const player_cmd_t	PLAYER_CMDS[] = {
	{ "Forward", player_cmd_forward, 7, 0,
		"Forward", "move up one tile" },
	{ "Right", player_cmd_right, 7, 0,
		"Right", "turn 90 degrees right" },
	{ "Left", player_cmd_left, 7, 0,
		"Left", "turn 90 degrees left" },
	{ "Look", player_cmd_look, 7, 0,
		"Look", "look around" },
	{ "Inventory", player_cmd_inventory, 1, 0,
		"Inventory", "inventory" },
	{ "Broadcast text", player_cmd_broadcast, 7, 0,
		"Broadcast text", "broadcast text" },
	{ "Connect_nbr", player_cmd_connect_nbr, 0, 0,
		"Connect_nbr", "number of team unused slots" },
	{ "Fork", player_cmd_fork, 42, 0,
		"Fork", "fork a player" },
	{ "Eject", player_cmd_eject, 7, 0,
		"Eject", "eject players from this tile" },
	{ "Take object", player_cmd_take, 7, 0,
		"Take object", "take object" },
	{ "Set object", player_cmd_set_obj_down, 7, 0,
		"Set object", "set object down" },
	{ "Incantation", player_cmd_incantation, 300, 0,
		"Incantation", "start incantation" }
};

static const player_cmd_t	SPECTATOR_CMDS[] = {
	{ "msz", spectate_cmd_map_size, 0, 0,
		"msz", "map size" },
	{ "bct", spectate_cmd_map_content_time, 0, 2,
		"bct X Y", "content of a tile" },
	{ "mct", spectate_cmd_content_map, 0, 0,
		"mct", "content of the map (all the tiles)" },
	{ "tna", spectate_cmd_name_teams, 0, 0,
		"tna", "name of all the teams" },
	{ "ppo", spectate_cmd_player_pos, 0, 1,
		"ppo #n", "player's position" },
	{ "plv", spectate_cmd_player_level, 0, 1,
		"plv #n", "player's level" },
	{ "pin", spectate_cmd_player_inventory, 0, 1,
		"pin #n", "player’s inventory" },
	{ "sgt", spectate_cmd_time_unit, 0, 0,
		"sgt", "time unit request" },
	{ "sst T", spectate_cmd_time_unit_mod, 0, 1,
		"sst", "time unit modification" }
};

void	player_cmd(char *cmd, ...)
{
	va_list			vargs;
	player_cmd_arg_t	args;
	const player_cmd_t	*c = NULL;
	int max_el = sizeof(PLAYER_CMDS) / sizeof(player_cmd_t);

	for (int i = 0; i < max_el; ++i) {
		if (strcmp(cmd, PLAYER_CMDS[i].cmd) == 0) {
			c = &PLAYER_CMDS[i];
			break;
		}
	}
	va_start(vargs, cmd);
	if (c) {
		args = (player_cmd_arg_t){ c, cmd, NULL };
		c->fct(&args, &vargs);
	}
	va_end(vargs);
}

void	spectate_cmd(char *cmd, ...)
{
	va_list			vargs;
	player_cmd_arg_t	args;
	const player_cmd_t	*c = NULL;
	int max_el = sizeof(SPECTATOR_CMDS) / sizeof(player_cmd_t);

	for (int i = 0; i < max_el; ++i) {
		if (strcmp(cmd, SPECTATOR_CMDS[i].cmd) == 0) {
			c = &SPECTATOR_CMDS[i];
			break;
		}
	}
	va_start(vargs, cmd);
	if (c) {
		args = (player_cmd_arg_t){ c, cmd, NULL };
		c->fct(&args, &vargs);
	}
	va_end(vargs);
}
