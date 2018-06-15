/*
** EPITECH PROJECT, 2018
** PSU_zappy_2017
** File description:
** player_cmd.c
*/

#include "player_cmd.h"
#include "str_to_tab.h"
#include <string.h>

static const player_cmd_t	ANONYMOUS_CMDS[] = {
	{ "SPECTATOR", anonymous_cmd_spectator, 0, 0,
		"", "select spectating mode" }
};
static const player_cmd_t	DEFAULT_ANONYMOUS_CMD = {
	"", anonymous_cmd_anonymous, 0, 0,
		"TEAM-NAME", "select a team"
};
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
static const player_cmd_t	DEFAULT_PLAYER_CMD = {
	"", player_cmd_error, 0, 0, "ko", "ko"
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
static const player_cmd_t	DEFAULT_SPECTATOR_CMD = {
	"", player_cmd_error, 0, 0, "ko", "ko"
};

static const size_t	MAX_ANONYMOUS_CMDS = SIZE_ARRAY(ANONYMOUS_CMDS);
static const size_t	MAX_PLAYER_CMDS = SIZE_ARRAY(PLAYER_CMDS);
static const size_t	MAX_SPECTATOR_CMDS = SIZE_ARRAY(SPECTATOR_CMDS);

static const player_cmd_t	*get_cmd(char **args,
	const player_cmd_t *cmds, int max_el)
{
	const player_cmd_t	*cmd = NULL;
	size_t	n = 0;

	if (!args || !(*args))
		return NULL;
	while (args && args[n] && args[++n]);
	for (int i = 0; i < max_el; ++i) {
		cmd = cmds + i;
		if (strcmp(*args, cmd->cmd) == 0 && cmd->nb_args == n - 1)
			break;
		cmd = NULL;
	}
	return cmd;
}

static const player_cmd_t	*get_client_cmd(
	char **args, client_t *client)
{
	const player_cmd_t *c = NULL;

	if (client->type == CLIENT_ANONYMOUS) {
		c = get_cmd(args, ANONYMOUS_CMDS, MAX_ANONYMOUS_CMDS);
		c = c ? c : &DEFAULT_ANONYMOUS_CMD;
	}
	if (client->type == CLIENT_PLAYER) {
		c = get_cmd(args, PLAYER_CMDS, MAX_PLAYER_CMDS);
		c = c ? c : &DEFAULT_PLAYER_CMD;
	}
	if (client->type == CLIENT_SPECTATOR) {
		c = get_cmd(args, SPECTATOR_CMDS, MAX_SPECTATOR_CMDS);
		c = c ? c : &DEFAULT_SPECTATOR_CMD;
	}
	return c;
}

bool	client_cmd(t_server *server, client_t *client, char *cmd)
{
	char			**cargs = str_to_tab(cmd, " \t");
	const player_cmd_t	*c = get_client_cmd(cargs, client);
	player_cmd_arg_t	args;

	if (c) {
		args = (player_cmd_arg_t){ c, cmd, cargs + 1 };
		c->fct(&args, server);
	}
	free_tab(cargs);
	return c != NULL;
}
