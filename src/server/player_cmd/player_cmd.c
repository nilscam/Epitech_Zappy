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
	{ "SPECTATOR", anonymous_cmd_spectator, NULL, 0, 0,
		"", "select spectating mode" }
};
static const player_cmd_t	DEFAULT_ANONYMOUS_CMD = {
	"", anonymous_cmd_anonymous, NULL, 0, 0,
		"TEAM-NAME", "select a team"
};
static const player_cmd_t	PLAYER_CMDS[] = {
	{ "Forward", player_cmd_forward, NULL, 7, 0,
		"Forward", "move up one tile" },
	{ "Right", player_cmd_right, NULL, 7, 0,
		"Right", "turn 90 degrees right" },
	{ "Left", player_cmd_left, NULL, 7, 0,
		"Left", "turn 90 degrees left" },
	{ "Look", player_cmd_look, NULL, 7, 0,
		"Look", "look around" },
	{ "Inventory", player_cmd_inventory, NULL, 1, 0,
		"Inventory", "inventory" },
	{ "Broadcast", player_cmd_broadcast, NULL, 7, -1,
		"Broadcast <text>", "broadcast text" },
	{ "Connect_nbr", player_cmd_connect_nbr, NULL, 0, 0,
		"Connect_nbr", "number of team unused slots" },
	{ "Fork", player_cmd_fork, validate_fork, 42, 0,
		"Fork", "fork a player" },
	{ "Eject", player_cmd_eject, validate_eject, 7, 0,
		"Eject", "eject players from this tile" },
	{ "Take", player_cmd_take, validate_take, 7, 1,
		"Take <object>", "take object" },
	{ "Set", player_cmd_set_obj_down, validate_set_obj_down, 7, 1,
		"Set <object>", "set object down" },
	{ "Incantation", player_cmd_incantation, validate_incant, 300, 0,
		"Incantation", "start incantation" }
};
static const player_cmd_t	DEFAULT_PLAYER_CMD = {
	"", player_cmd_error, NULL, 0, 0, "ko", "ko"
};
static const player_cmd_t	SPECTATOR_CMDS[] = {
	{ "msz", spectate_cmd_map_size, NULL, 0, 0,
		"msz", "map size" },
	{ "bct", spectate_cmd_map_content_tile, NULL, 0, 2,
		"bct X Y", "content of a tile" },
	{ "mct", spectate_cmd_content_map, NULL, 0, 0,
		"mct", "content of the map (all the tiles)" },
	{ "tna", spectate_cmd_name_teams, NULL, 0, 0,
		"tna", "name of all the teams" },
	{ "ppo", spectate_cmd_player_pos, NULL, 0, 1,
		"ppo #n", "player's position" },
	{ "plv", spectate_cmd_player_level, NULL, 0, 1,
		"plv #n", "player's level" },
	{ "pin", spectate_cmd_player_inventory, NULL, 0, 1,
		"pin #n", "player’s inventory" },
	{ "sgt", spectate_cmd_time_unit, NULL, 0, 0,
		"sgt", "time unit request" },
	{ "sst", spectate_cmd_time_unit_mod, NULL, 0, 1,
		"sst T", "time unit modification" },
	{ "pnw", spectate_cmd_players_pos, NULL, 0, 0,
		"pnw", "position of all players" },
	{ "egg", spectate_cmd_eggs_pos, NULL, 0, 0,
		"egg", "position of all eggs" }
};
static const player_cmd_t	DEFAULT_SPECTATOR_CMD = {
	"", spectate_cmd_error, NULL, 0, 0, "ko", "ko"
};

static const size_t	MAX_ANONYMOUS_CMDS = SIZE_ARRAY(ANONYMOUS_CMDS);
static const size_t	MAX_PLAYER_CMDS = SIZE_ARRAY(PLAYER_CMDS);
static const size_t	MAX_SPECTATOR_CMDS = SIZE_ARRAY(SPECTATOR_CMDS);

static const player_cmd_t	*get_cmd(char **args,
	const player_cmd_t *cmds, int max_el)
{
	const player_cmd_t	*cmd = NULL;
	int	n = 0;

	if (!args || !(*args))
		return NULL;
	while (args && args[n] && args[++n]);
	for (int i = 0; i < max_el; ++i) {
		cmd = cmds + i;
		if (strcmp(*args, cmd->cmd) == 0
			&& (cmd->nb_args < 0 || cmd->nb_args == n - 1))
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

static void	client_callback_cmd(player_cmd_arg_t *args)
{
	const player_cmd_t	*c = args->c;

	DEBUG("calling callback to fd %d : %s - %s",
		args->client->_fd, c->prototype, c->description);
	c->fct(args);
	free_tab(args->args);
	SAFE_FREE(args->cmd);
	free(args);
}

static void	call_client_cmd(player_cmd_arg_t *args)
{
	const player_cmd_t	*c = args->c;
	player_t		*player = args->player;
	int			time_limit = c->time_limit;
	player_cmd_arg_t	*args_cp = NULL;
	bool			exec = !c->validate || c->validate(args);

	if (exec && time_limit > 0 && args->client->type == CLIENT_PLAYER)
		args_cp = malloc(sizeof(player_cmd_arg_t));
	if (exec && args_cp) {
		memcpy(args_cp, args, sizeof(player_cmd_arg_t));
		player_wait_for(player, time_limit);
		player_set_is_busy_callback(player,
			(pl_callback_t)client_callback_cmd, args_cp);
	} else {
		DEBUG("calling to %d : %s - %s (exec=%d)",
			args->client->_fd, c->prototype, c->description, exec);
		if (exec)
			c->fct(args);
		free_tab(args->args);
		SAFE_FREE(args->cmd);
	}
}

bool	client_cmd(t_server *serv, client_t *client, char *cmd, player_t *pl)
{
	char			**tab = str_to_tab(cmd, " \t");
	const player_cmd_t	*c = get_client_cmd(tab, client);
	int			nb_args = 0;
	player_cmd_arg_t	args;

	while (tab && tab[nb_args])
		++nb_args;
	args = (player_cmd_arg_t){ c, strdup(cmd), tab, nb_args,
		client, serv, pl };
	if (c && tab) {
		call_client_cmd(&args);
	}
	return c != NULL;
}
